//
// Created by razvan on 11/5/24.
//
#include "main.h"

#include <atomic>


using namespace m1;

Main::Main(): meshGenerator(meshes),
              tankA(terrain_pixel_frequency, terrain_x, terrain_y),
              tankB(terrain_pixel_frequency, terrain_x, terrain_y)
{
}


Main::~Main()
{
}

void Main::InitCameraPosition() {
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
}

float get_dif_angle(float t1, float t2) {
    if (t1 < 0 && t2 < 0) {
        return -t2 - t1 ;
    }
    if (t1 < 0) {
        return M_PI - t2 + t1;
    }
    if (t2 < 0) {
        return M_PI - t1 + t2;
    }
    return M_PI - t1 + t2;

}

void Main::Init()
{
    resolution = window->props.resolution;

    InitCameraPosition();

    terrain_x = vector<float>(resolution.x / terrain_pixel_frequency + 1);
    terrain_y = vector<float>(resolution.x / terrain_pixel_frequency + 1, 0);

    for (int i = 0; i < terrain_frequency.size(); i++) {
        terrain_frequency[i] *= resolution.x / 14;
    }

    for (int i = 0; i < terrain_amplitude.size(); i++) {
        terrain_amplitude[i] *= resolution.y / 14;
    }

    for (int i = 0; i < terrain_y.size(); i++) {
        terrain_x[i] = i * terrain_pixel_frequency;

        for (int j = 0; j < terrain_amplitude.size(); j++) {
            terrain_y[i] += terrain_amplitude[j] * sin(terrain_x[i] / terrain_frequency[j]);
        }
        terrain_y[i] = resolution.y/3 - terrain_y[i];
    }

    terrain_small_threshold = 0.02;

    // Create base square
    meshGenerator.CreateBaseSquareMesh();
    meshGenerator.CreateTracksMesh();
    meshGenerator.CreateMainTankDesertYellowBoxMesh();
    meshGenerator.CreateDesertYellowSemiCircleMesh();
    meshGenerator.CreateMainTankCamoGreenBoxMesh();
    meshGenerator.CreateCamoGreenCircleMesh();
    meshGenerator.CreateCannonMesh();
    meshGenerator.CreateCircleMesh();
    meshGenerator.CreateWhiteCircleMesh();
    meshGenerator.CreateHealthSquare(health(), "health");
    meshGenerator.CreateHealthSquare(frame(), "frame");

    tankA.x = resolution.x / 4;
    tankA.y = tankA.TankY(tankA.x);
    tankA.angle = tankA.TankAngle(tankA.x);
    tankA.cannonAngle = M_PI/12;

    tankB.x = resolution.x - resolution.x / 4;
    tankB.y = tankB.TankY(tankB.x);
    tankB.angle = tankB.TankAngle(tankB.x);
    tankB.cannonAngle = M_PI - M_PI/12;
}


void Main::FrameStart()
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

int f= 0;
void Main::Update(float deltaTimeSeconds)
{






    if (dronestrike) {
        if (f < 20) {
            for (int i = 0; i < rand()% 100 ; i++) {
                Ammo newAmmo = Ammo(min(8, rand()%10));
                newAmmo.time = 0;
                newAmmo.x_start = rand() % resolution.x;
                newAmmo.y_start = resolution.y;
                newAmmo.angle = -M_PI/2;
                tankA.shells.push_back(newAmmo);

                tankA.flyingAmmo = true;
            }
            f++;
        } else {
            f = 0;
            dronestrike = false;
        }
    }
    if (tankA.health <= 0 && tankA.alive) {
        cout << "\n\n=====================================================\nVICTORY FOR PLAYER 2!\n";
        // window->Close();
        tankA.alive = false;
    }

    if (tankB.health <= 0 && tankB.alive) {
        cout << "\n\n=====================================================\nVICTORY FOR PLAYER 1!\n";
        // window->Close();
        tankB.alive = false;
    }
    float A_x = 0, A_y = terrain_y[0], B_x;
    if (terrain_y[0] < 10) {
        terrain_y[0] = 10;
    }
    if (terrain_y[terrain_y.size() - 1] < 10) {
        terrain_y[terrain_y.size() - 1] = 10;
    }

    if (window->KeyHold(GLFW_KEY_D) == GLFW_PRESS && window->KeyHold(GLFW_KEY_A) != GLFW_PRESS && tankA.x < resolution.x - 2) {
        tankA.x += 50 * deltaTimeSeconds * (tankA.angle >= 0 ? cos(tankA.angle) : 1 - sin(tankA.angle));
    }

    if (window->KeyHold(GLFW_KEY_A) == GLFW_PRESS && window->KeyHold(GLFW_KEY_D) != GLFW_PRESS && tankA.x > 2) {
        tankA.x -= 50 * deltaTimeSeconds * (tankA.angle < 0 ? cos(tankA.angle) : 1 + sin(tankA.angle));
    }

    if (window->KeyHold(GLFW_KEY_W) == GLFW_PRESS && tankA.cannonAngle < M_PI - M_PI/16) {
        tankA.cannonAngle += deltaTimeSeconds/5;
    }

    if (window->KeyHold(GLFW_KEY_S) == GLFW_PRESS && tankA.cannonAngle > M_PI/16) {
        tankA.cannonAngle -= deltaTimeSeconds/5;
    }

    tankA.y = tankA.TankY(tankA.x);
    tankA.angle = tankA.TankAngle(tankA.x);

    if (window->KeyHold(GLFW_KEY_RIGHT) == GLFW_PRESS && window->KeyHold(GLFW_KEY_LEFT) != GLFW_PRESS && tankB.x < resolution.x - 2) {
        tankB.x += 50 * deltaTimeSeconds * (tankB.angle >= 0 ? cos( tankB.angle) : 1 - sin(tankB.angle));
    }

    if (window->KeyHold(GLFW_KEY_LEFT) == GLFW_PRESS && window->KeyHold(GLFW_KEY_RIGHT) != GLFW_PRESS &&  tankB.x > 2) {
        tankB.x -= 50 * deltaTimeSeconds * (tankB.angle < 0 ? cos( tankB.angle) : 1 + sin(tankB.angle));
    }

    if (window->KeyHold(GLFW_KEY_UP) == GLFW_PRESS && tankB.cannonAngle < M_PI - M_PI/16) {
        tankB.cannonAngle += deltaTimeSeconds/5;
    }

    if (window->KeyHold(GLFW_KEY_DOWN) == GLFW_PRESS && tankB.cannonAngle > M_PI/16) {
        tankB.cannonAngle -= deltaTimeSeconds/5;
    }

    tankB.y = tankB.TankY(tankB.x);
    tankB.angle = tankB.TankAngle(tankB.x);

    if (showHitBox) {
        for (int i = 0; i < resolution.x; i+= 5) {
            for (int j = 0; j < resolution.y; j+= 5) {
                float AHit_x = (tankA.x - i - 24.0 * sin(tankA.angle)) * cos(-tankA.angle) - (tankA.y - j + 24.0*cos(tankA.angle)) * sin(-tankA.angle);
                float AHit_y = (tankA.x - i - 24.0 * sin(tankA.angle)) * sin(-tankA.angle) + (tankA.y - j + 24.0*cos(tankA.angle)) * cos(-tankA.angle);

                float BHit_x = (tankB.x - i - 24.0 * sin(tankB.angle)) * cos(-tankB.angle) - (tankB.y - j + 24.0*cos(tankB.angle)) * sin(-tankB.angle);
                float BHit_y = (tankB.x - i - 24.0 * sin(tankB.angle)) * sin(-tankB.angle) + (tankB.y - j + 24.0*cos(tankB.angle)) * cos(-tankB.angle);
                if (tankA.alive && pow(AHit_x/2.4, 2) + pow(AHit_y/1.5, 2) < 400) {
                    // cout << "Hit!! " << eHit_x << " " << eHit_y  << " " << tankA.angle * 180 / M_PI<<"\n";
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(i, j);
                    modelMatrix *= transform2D::Scale(2, 2);
                    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
                }

                if (tankB.alive && pow(BHit_x/2.4, 2) + pow(BHit_y/1.5, 2) < 400) {
                    // cout << "Hit!! " << eHit_x << " " << eHit_y  << " " << tankA.angle * 180 / M_PI<<"\n";
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(i, j);
                    modelMatrix *= transform2D::Scale(2, 2);
                    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
                }
            }
        }
    }
    for (int i = 1; i < terrain_x.size() - 1; i++) {
        // AVG LANDSLIDE
         float avg = terrain_y[i - 1] + terrain_y[i] + terrain_y[i + 1];
         avg /= 3;
         if (abs(avg - terrain_y[i]) > terrain_small_threshold) {
             terrain_y[i] += (avg - terrain_y[i]) / 2;
         }

        if (terrain_y[i] < 10) {
            terrain_y[i] = 10;
        }

        B_x = terrain_x[i];
        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(A_x, A_y);
        modelMatrix *= transform2D::Shear((terrain_y[i] - A_y) / (B_x - A_x));
        modelMatrix *= transform2D::Scale(B_x - A_x, max(A_y, terrain_y[i]));

        A_x = B_x;
        A_y = terrain_y[i];

        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
    }

    if (tankA.alive) {
        modelMatrix = tankA.CannonMatrix();
        RenderMesh2D(meshes["cannon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankA.TurretMatrix();
        RenderMesh2D(meshes["desert_yellow_semi_circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankA.BodyMatrix();
        RenderMesh2D(meshes["desert_yellow_body"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankA.TracksMatrix();
        RenderMesh2D(meshes["tracks"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankA.HealthMatrix();
        RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankA.HealthFrameMatrix();
        RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);

        for (int i = 1; i < 60; i++) {
            float px = tankA.predX(i*5, tankA.ammo_x, tankA.ammo_angle);
            float py = tankA.predY(i*5, tankA.ammo_y, tankA.ammo_angle);

            modelMatrix = tankA.getPredMatrix(px, py);
            RenderMesh2D(meshes["white_circle"], shaders["VertexColor"], modelMatrix);
        }
    }
    tankA.UpdateAmmoPos(deltaTimeSeconds * 100, tankB);

    if (tankA.flyingAmmo) {
        for (int i = 0; i < tankA.shells.size(); i++) {
            Ammo ammo = tankA.shells[i];

            modelMatrix = ammo.getModelMatrix();
            RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
        }
    }

    if (tankB.alive) {
        modelMatrix = tankB.CannonMatrix();
        RenderMesh2D(meshes["cannon"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankB.TurretMatrix();
        RenderMesh2D(meshes["camo_green_semi_circle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankB.BodyMatrix();
        RenderMesh2D(meshes["camo_green_body"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankB.TracksMatrix();
        RenderMesh2D(meshes["tracks"], shaders["VertexColor"], modelMatrix);

        modelMatrix = tankB.HealthMatrix();
        RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);


        modelMatrix = tankB.HealthFrameMatrix();
        RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);

        for (int i = 1; i < 60; i++) {
            float px = tankB.predX(i*5, tankB.ammo_x, tankB.ammo_angle);
            float py = tankB.predY(i*5, tankB.ammo_y, tankB.ammo_angle);

            modelMatrix = tankB.getPredMatrix(px, py);
            RenderMesh2D(meshes["white_circle"], shaders["VertexColor"], modelMatrix);
        }
    }
    tankB.UpdateAmmoPos(deltaTimeSeconds * 100, tankA);

    if (tankB.flyingAmmo) {
        for (int i = 0; i < tankB.shells.size(); i++) {
            Ammo ammo = tankB.shells[i];

            modelMatrix = ammo.getModelMatrix();
            RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
        }
    }

    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(1050, 600);
    // modelMatrix *= transform2D::Scale(60, 40);
    // RenderMesh2D(meshes["white_circle"], shaders["VertexColor"], modelMatrix);
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(1000, 600);
    // modelMatrix *= transform2D::Scale(50, 50);
    // RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
    //
    // modelMatrix = glm::mat3(1);
    // modelMatrix *= transform2D::Translate(1000, 600);
    // modelMatrix *= transform2D::Scale(110, 110);
    // RenderMesh2D(meshes["white_circle"], shaders["VertexColor"], modelMatrix);
}


void Main::FrameEnd()
{

}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Main::OnInputUpdate(float deltaTime, int mods)
{

}

int passcode = 0;
void Main::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE && tankA.fireCooldown == 0) {
        tankA.ShootAmmo();
    }
    if (key == GLFW_KEY_ENTER && tankB.fireCooldown == 0) {
        tankB.ShootAmmo();
    }

    if (key == GLFW_KEY_F3) {
        showHitBox = !showHitBox;
    }

    if (key == GLFW_KEY_O) {
        passcode = 1;
    }
    if (key == GLFW_KEY_B && passcode == 1) {
        passcode = 2;
    }
    if (key == GLFW_KEY_A && passcode == 2) {
        passcode = 3;
    }
    if (key == GLFW_KEY_M && passcode == 3) {
        passcode = 4;
    }
    if (key == GLFW_KEY_A && passcode == 4) {
        passcode = 0;
        dronestrike = true;
    }
}


void Main::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Main::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Main::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Main::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Main::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Main::OnWindowResize(int width, int height)
{
    // Treat window resize event
}


