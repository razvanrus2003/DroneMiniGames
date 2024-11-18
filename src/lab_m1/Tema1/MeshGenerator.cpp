//
// Created by razvan on 11/7/24.
//

#include "MeshGenerator.h"

using namespace std;

MeshGenerator::MeshGenerator(unordered_map<std::string, Mesh *> &meshes):meshes(meshes) {
}
MeshGenerator::~MeshGenerator() {

}

void MeshGenerator::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    // TODO(student): Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    unsigned int IBO = 0;
    // TODO(student): Create the IBO and bind it
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // TODO(student): Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    // cout << (*meshes).size() << endl;
}

void MeshGenerator::CreateBaseSquareMesh() {
    vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  0), terrain_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  0), terrain_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, -1,  0), terrain_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, -1,  0), terrain_color(), glm::vec3(0.2, 0.8, 0.6)),
        };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 3, 2,
    };

    // Actually create the mesh from the data
    // cout << meshes.size() << endl;
    CreateMesh("square", vertices, indices);
    // cout << meshes.size() << endl;
}

void MeshGenerator::CreateTracksMesh() {
    vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(1, 0,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-1, 0,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-2, 1,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(2, 1,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
        };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 3, 2,
    };

    // Actually create the mesh from the data
    CreateMesh("tracks", vertices, indices);
}

void MeshGenerator::CreateMainTankDesertYellowBoxMesh() {
    vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(2, 0,  0), tank_body_yellow_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-2, 0,  0), tank_body_yellow_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-1.3f, 1,  0), tank_body_yellow_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1.3f, 1,  0), tank_body_yellow_color(), glm::vec3(0.2, 0.8, 0.6)),
        };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 3, 2,
    };

    // Actually create the mesh from the data
    CreateMesh("desert_yellow_body", vertices, indices);
}

void MeshGenerator::CreateMainTankCamoGreenBoxMesh() {
    vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(2, 0,  0), tank_body_green_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-2, 0,  0), tank_body_green_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-1.3f, 1,  0), tank_body_green_color(), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1.3f, 1,  0), tank_body_green_color(), glm::vec3(0.2, 0.8, 0.6)),
        };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 3, 2,
    };

    // Actually create the mesh from the data
    CreateMesh("camo_green_body", vertices, indices);
}

void MeshGenerator::CreateDesertYellowSemiCircleMesh() {
    vector<VertexFormat> vertices;

    glm::vec3 point = glm::vec3(0, 0, 0);
    vertices.emplace_back(point, tank_body_yellow_color(), glm::vec3(0.2, 0.8, 0.6));

    for (int i = 0; i <= 180; i++) {
        point = glm::vec3(cos(i * (M_PI/180)), sin(i * (M_PI/180)), 0.0f);
        vertices.emplace_back(point, tank_body_yellow_color(), glm::vec3(0.2, 0.8, 0.6));
    }

    vector<unsigned int> indices;

    for (int i = 1; i <= 180; i++) {
        indices.emplace_back(0);
        indices.emplace_back(i);
        indices.emplace_back(i + 1);
    }

    CreateMesh("desert_yellow_semi_circle", vertices, indices);
}

void MeshGenerator::CreateCamoGreenCircleMesh() {
    vector<VertexFormat> vertices;

    glm::vec3 point = glm::vec3(0, 0, 0);
    vertices.emplace_back(point, tank_body_green_color(), glm::vec3(0.2, 0.8, 0.6));

    for (int i = 0; i <= 180; i++) {
        point = glm::vec3(cos(i * (M_PI/180)), sin(i * (M_PI/180)), 0.0f);
        vertices.emplace_back(point, tank_body_green_color(), glm::vec3(0.2, 0.8, 0.6));
    }

    vector<unsigned int> indices;

    for (int i = 1; i <= 180; i++) {
        indices.emplace_back(0);
        indices.emplace_back(i);
        indices.emplace_back(i + 1);
    }

    CreateMesh("camo_green_semi_circle", vertices, indices);
}

void MeshGenerator::CreateCannonMesh() {
    vector<VertexFormat> vertices
      {
          VertexFormat(glm::vec3(0, -1,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
          VertexFormat(glm::vec3(1, -1,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
          VertexFormat(glm::vec3(1, 1,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
          VertexFormat(glm::vec3(0, 1,  0), tracks_color(), glm::vec3(0.2, 0.8, 0.6)),
      };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 3, 2,
    };

    // Actually create the mesh from the data
    CreateMesh("cannon", vertices, indices);
}

void MeshGenerator::CreateCircleMesh() {
    vector<VertexFormat> vertices;

    glm::vec3 point = glm::vec3(0, 0, 0);
    vertices.emplace_back(point, ammo_color(), glm::vec3(0.2, 0.8, 0.6));

    for (int i = 0; i < 360; i++) {
        point = glm::vec3(cos(i * (2*M_PI/360)), sin(i * (2*M_PI/360)), 0.0f);
        vertices.emplace_back(point, ammo_color(), glm::vec3(0.2, 0.8, 0.6));
    }

    vector<unsigned int> indices;

    for (int i = 1; i <= 360; i++) {
        indices.emplace_back(0);
        indices.emplace_back(i);
        indices.emplace_back(i + 1);
    }
    indices.emplace_back(0);
    indices.emplace_back(360);
    indices.emplace_back(1);

    CreateMesh("circle", vertices, indices);
}

void MeshGenerator::CreateWhiteCircleMesh() {
    vector<VertexFormat> vertices;

    glm::vec3 point = glm::vec3(0, 0, 0);
    vertices.emplace_back(point, pread_color(), glm::vec3(0.2, 0.8, 0.6));

    for (int i = 0; i < 360; i++) {
        point = glm::vec3(cos(i * (2*M_PI/360)), sin(i * (2*M_PI/360)), 0.0f);
        vertices.emplace_back(point, pread_color(), glm::vec3(0.2, 0.8, 0.6));
    }

    vector<unsigned int> indices;

    for (int i = 1; i <= 360; i++) {
        indices.emplace_back(0);
        indices.emplace_back(i);
        indices.emplace_back(i + 1);
    }
    indices.emplace_back(0);
    indices.emplace_back(360);
    indices.emplace_back(1);

    CreateMesh("white_circle", vertices, indices);
}

void MeshGenerator::CreateHealthSquare(glm::vec3 color, const char* name) {
    vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  0), color, glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, 0,  0), color, glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(1, -1,  0), color, glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, -1,  0), color, glm::vec3(0.2, 0.8, 0.6)),
        };

    vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 3, 2,
    };

    // Actually create the mesh from the data
    // cout << meshes.size() << endl;
    CreateMesh(name, vertices, indices);
    // cout << meshes.size() << endl;
}

