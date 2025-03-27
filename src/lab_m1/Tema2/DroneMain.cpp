//
// Created by razvan on 12/1/24.
//

#include "DroneMain.h"

#include "droneUtil/colors.h"

using namespace m1;


DroneMain::DroneMain(): generator(meshes, shaders),
                        resolution(window->GetResolution())
                        {
    this->drone = new Drone(this);
    this->drone_hitBox = new DroneHitBox(drone_position, 4, this);
    this->physics_engine = new physicsEngine();
}

DroneMain::~DroneMain() {
}

void DroneMain::RenderMesh(string mesh, const glm::mat4 &modelMatrix, const glm::vec3 &color) {
    RenderMesh(meshes[mesh], modelMatrix, color);
}

void DroneMain::RenderMesh(string mesh, string shader, const glm::mat4 & modelMatrix, const glm::vec3 &color1, const glm::vec3 &color2) {
    RenderMesh(meshes[mesh], shaders[shader], modelMatrix, color1, color2, 1);
}

void DroneMain::RenderMesh(Mesh *mesh, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
    RenderMesh(mesh, shaders["Normal"], modelMatrix, color, color, 1);
}

void DroneMain::RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color1, const glm::vec3 &color2, const float resolution)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int location = glGetUniformLocation(shader->program, "Model");
    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // TODO(student): Get shader location for uniform mat4 "View"
    int view = glGetUniformLocation(shader->program, "View");
    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int projection = glGetUniformLocation(shader->program, "Projection");
    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int time = glGetUniformLocation(shader->program, "Time");
    GLfloat timeVal = (float)Engine::GetElapsedTime();
    glUniform1f(time, timeVal);

    int camPos = glGetUniformLocation(shader->program, "CameraPosition");
    glUniform3f(camPos, (drone_position.x + camera_distances.x) / 1, (drone_position.y + camera_distances.y) / 1, (drone_position.z + camera_distances.z) / 1);

    int fogColPos = glGetUniformLocation(shader->program, "FogColor");
    glUniform3f(fogColPos, fog_color()[0], fog_color()[1], fog_color()[2]);

    int shColor = glGetUniformLocation(shader->program, "Color1");
    glUniform3f(shColor, color1[0], color1[1], color1[2]);

    shColor = glGetUniformLocation(shader->program, "Color2");
    glUniform3f(shColor, color2[0], color2[1], color2[2]);

    int resLoc = glGetUniformLocation(shader->program, "Resolution");
    glUniform1f(resLoc, resolution);

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);

    mesh->Render();
}

void DroneMain::InitCameraPosition() {
    auto camera = GetSceneCamera();
    camera->SetPerspective(100, 16./9., 0.1f, 10000);

    camera->SetPosition(drone_position + camera_distances);
    camera->SetRotation(glm::vec3(drone_rotating + camera_rotation));

    GetCameraInput()->SetActive(false);

    camera->Update();
}

void DroneMain::Init()
{
    InitCameraPosition();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    generator.CreateTerrainMesh("Terrain", terrain_color(), terrain.vertexCount);
    generator.CreateCubeMesh("Cube", stone_color());
    generator.CreateCylinderMesh("Cylinder", stone_color(), 200);
    generator.CreateConMesh("Con", stone_color(), 200);
    generator.CreateGraveStoneMesh("GraveStone", stone_color(), 20);

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }


    generator.CreateShader(window->props.selfDir, "Terrain", "Terrain.glsl", "SimplexNoise.glsl");
    generator.CreateShader(window->props.selfDir, "Normal", "Normal.glsl", "Normal.glsl");

    generator.CreateShader(window->props.selfDir, "Propeller", "Propeller.glsl", "Propeller.glsl");
    generator.CreateShader(window->props.selfDir, "Rotor", "RotorBlade.glsl", "RotorEffect.glsl");
    generator.CreateShader(window->props.selfDir, "Con", "Con.glsl", "Normal.glsl");
    generator.CreateShader(window->props.selfDir, "Grave", "Grave.glsl", "Grave.glsl");

    generator.CreateShader(window->props.selfDir, "GravePic", "GravePic.glsl", "GravePic.glsl");
    generator.CreateShader(window->props.selfDir, "HitBox", "Normal.glsl", "HitBox.glsl");

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= Scale(terrain.scale.x, terrain.scale.y, terrain.scale.z);
    Cube* terrain_shape = new Cube(glm::vec3(0, 0, 0), glm::vec3(terrain.vertexCount, 1, terrain.vertexCount), modelMatrix, "Terrain", "Terrain", 0);

    shapes.push_back(terrain_shape);
    physics_engine->addTerrain(terrain_shape, terrain);

    for (int i = 0 ;i < 150; i++) {
        graves_init.push_back((rand() % 164000) / 41);

        int x = rand() % 5000;
        int z = rand() % 5000;

        glm::mat4 modelMatrix2 = glm::mat4(1);
        modelMatrix2 *= Translate(x, terrain.getHeights(x, z) + 25, z);
        float angle = ((int)graves_init[i] % 5) * M_PI / 30;
        modelMatrix2 *= RotateOY(angle);
        modelMatrix2 *= Scale(20, 25, 5);

        Cube* stone = new Cube(glm::vec3(-1.1, -1, -1.3), glm::vec3(1.1, 1, 1.3), modelMatrix2, "GraveStone", "Grave", graves_init[i]);

        shapes.push_back(stone);
        physics_engine->addShape(stone);
    }

    tree = new Tree(glm::vec3(2000, terrain.getHeights(2000,2000), 2000), 60, 10, this);
}


void DroneMain::FrameStart()
{
    // Sets the clear color for the color buffer

    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(SKY_R, SKY_G, SKY_B, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

}

void DroneMain::Update(float deltaTimeSeconds)
{
    time += deltaTimeSeconds;
    glm::mat4 modelMatrix;

    RenderMesh(meshes[shapes[0]->mesh_name],shaders[shapes[0]->shader_name], shapes[0]->modelMatrix, fog_color(), grass_color(), terrain.resolution);

    for (int i = 1; i < shapes.size(); i++) {
        RenderMesh(meshes[shapes[i]->mesh_name], shaders[shapes[i]->shader_name], shapes[i]->modelMatrix, stone_color(), stone_color(), graves_init[i - 1]);

        modelMatrix = shapes[i]->modelMatrix;

        modelMatrix *= Scale(.36, .24, 1.2);
        modelMatrix *= RotateOX(M_PI / 2);
        RenderMesh(meshes["Cylinder"], shaders["GravePic"], modelMatrix, stone_color(), stone_color(), 1);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix *= Translate(drone_position.x, drone_position.y, drone_position.z);
    modelMatrix *= RotateOY(drone_rotating.y);
    modelMatrix *= RotateOY(drone_model_rot.y);
    // modelMatrix *= Scale(.5, .5, .5);


    tree->Render();
    drone->RenderDrone(modelMatrix, time);

    if (show_hitBox) {
        for (int i = 1; i < shapes.size(); i++) {

            glm::mat4 modelMatrix2 = shapes[i]->getHitBoxModelMatrix();

            RenderMesh(meshes["Cube"], shaders["HitBox"], modelMatrix2, hitBox_color(), hitBox_color(), 1);
        }

        drone_hitBox->Render(modelMatrix);
    }
    // modelMatrix *= Scale(drone_hitBox.radius * 2, drone_hitBox.radius * 2, drone_hitBox.radius * 2);
    // RenderMesh(meshes["sphere"], shaders["HitBox"], modelMatrix, drone_color(), hitBox_color(), 1);
}


void DroneMain::FrameEnd()
{
    // DrawCoordinateSystem();
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void DroneMain::OnInputUpdate(float deltaTime, int mods)
{
    auto camera = GetSceneCamera();

    glm::mat4 modelMatrix = glm::mat4(1);
    glm::vec3 delta_move = glm::vec3(0, 0, 0);

    int speed;
    if (window->KeyHold(GLFW_KEY_LEFT_SHIFT)) {
        speed = 10;
    } else {
        speed = 100;
    }
    deltaTime *= speed;

    vec3 old_pos = drone_position;
    vec3 old_rot = drone_rotating;

    if (window->KeyHold(GLFW_KEY_W)) {
        delta_move.z -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        delta_move.z += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        delta_move.x -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        delta_move.x += deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_Q)) {
        delta_move.y -= deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_E)) {
        delta_move.y += deltaTime;
    }

    modelMatrix *= RotateOY(drone_rotating.y);
    delta_move = modelMatrix * glm::vec4(delta_move.x, delta_move.y, delta_move.z, 1);
    drone_position = drone_position + delta_move;

    drone_hitBox->update(drone_position, drone_rotating.y + drone_model_rot.y);

    if (physics_engine->checkCollisionWithEnv(drone_hitBox)) {
        collision = true;
        cout << drone_position << endl;

        cout << "Collision detected" << endl;
        drone_position = old_pos;
        drone_hitBox->update(drone_position, drone_rotating.y + drone_model_rot.y);
    }
    modelMatrix *= RotateOX(camera_rotation.x);
    glm::vec3 cam_rot_distances = modelMatrix * glm::vec4(camera_distances.x, camera_distances.y, camera_distances.z, 1);
    camera->SetPosition(drone_position + cam_rot_distances);
    camera->Update();
}

void DroneMain::OnKeyPress(int key, int mods)
{

}


void DroneMain::OnKeyRelease(int key, int mods)
{
    // Add key release event
    if (key == GLFW_KEY_F3) {
        // Add key release event
        show_hitBox = !show_hitBox;
    }
}


void DroneMain::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    auto camera = GetSceneCamera();

    // Add mouse move event
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 old_rotation = drone_rotating;
        camera_rotation += glm::vec3((-(float)deltaY/1000), 0, 0);
        drone_rotating += glm::vec3(0, (-(float)deltaX/1000), 0);

        drone_hitBox->update(drone_position, drone_rotating.y + drone_model_rot.y);

        if (physics_engine->checkCollisionWithEnv(drone_hitBox)) {
            collision = true;
            cout << drone_position << endl;

            cout << "Collision detected" << endl;
            drone_rotating = old_rotation;
            drone_hitBox->update(drone_position, drone_rotating.y + drone_model_rot.y);
        }
        camera->SetRotation(drone_rotating + camera_rotation);
        camera->Update();

    }
}


void DroneMain::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT))
    {
        window->DisablePointer();
    }
}


void DroneMain::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT))
    {
        window->ShowPointer();
    }
}


void DroneMain::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void DroneMain::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
