//
// Created by razvan on 11/7/24.
//

#include "Generator.h"

using namespace std;

Generator::Generator(unordered_map<std::string, Mesh *> &meshes, unordered_map<std::string, Shader *> &shaders) : meshes(meshes), shaders(shaders) {

}
Generator::~Generator() {

};

void Generator::CreateShader(string window_path ,const char *name, const char *vertexShader, const char *fragmentShader)
{
    // Create a shader program for drawing face polygon with the color of the normal
    Shader *shader = new Shader(name);
    shader->AddShader(PATH_JOIN(window_path, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShaders", vertexShader), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window_path, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShaders", fragmentShader), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
}

void Generator::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
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
}

void Generator::CreateTerrainMesh(const char *name, glm::vec3 color, int vertexCount) {
    int n = vertexCount;

    vector<VertexFormat> vertices = vector<VertexFormat>();
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            vertices.push_back(VertexFormat(glm::vec3(i, 0, j), color, glm::vec3(0.2, 0.8, 0.6)));
        }
    }

    vector<unsigned int> indices = vector<unsigned int>();
    for (int i = 0; i < n * n - n; i+= n) {
        for (int j = 0; j < n - 1; j++) {
            indices.push_back(i + j);
            indices.push_back(i + j + 1);
            indices.push_back(i + j + n);
        }
    }

    for (int i = n; i < n * n; i+= n) {
        for (int j = 0; j < n - 1; j++) {
            indices.push_back(i + j);
            indices.push_back(i + j + 1);
            indices.push_back(i + j + 1 - n);
        }
    }

    // Actually create the mesh from the data
    CreateMesh(name, vertices, indices);
}

void Generator::CreateCubeMesh(const char *name, glm::vec3 color) {
    vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
            VertexFormat(glm::vec3( 1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
            VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
            VertexFormat(glm::vec3( 1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
            VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
            VertexFormat(glm::vec3( 1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
            VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
            VertexFormat(glm::vec3( 1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
        };

    vector<unsigned int> indices =
    {
        0, 1, 2,        1, 3, 2,
        2, 3, 7,        2, 7, 6,
        1, 7, 3,        1, 5, 7,
        6, 7, 4,        7, 5, 4,
        0, 4, 1,        1, 4, 5,
        2, 6, 4,        0, 2, 4,
    };

    CreateMesh(name, vertices, indices);
}

void Generator::CreateCylinderMesh(const char *name, glm::vec3 color, int vertexCount) {
    int n = vertexCount;

    vector<VertexFormat> vertices = vector<VertexFormat>();

    //  0
    vertices.push_back(VertexFormat(glm::vec3(0, 1, 0), color, glm::vec3(0.2, 0.8, 0.6)));
    //  [1 -> n]
    for (int i = 0; i < n; i++) {
        float x = cos(2 * M_PI / n * i);
        float z = sin(2 * M_PI / n * i);
        vertices.push_back(VertexFormat(glm::vec3(x, 1, z), color, glm::vec3(0.2, 0.8, 0.6)));
    }

    //  n+1
    vertices.push_back(VertexFormat(glm::vec3(0, -1, 0), color, glm::vec3(0.2, 0.8, 0.6)));
    // [n+2 -> 2n+1]
    for (int i = 0; i < n; i++) {
        float x = cos(2 * M_PI / n * i);
        float z = sin(2 * M_PI / n * i);
        vertices.push_back(VertexFormat(glm::vec3(x, -1, z), color, glm::vec3(0.2, 0.8, 0.6)));
    }

    //  [2n + 2 -> 3n + 1]
    for (int i = 0; i < n; i++) {
        float x = cos(2 * M_PI / n * i);
        float z = sin(2 * M_PI / n * i);
        vertices.push_back(VertexFormat(glm::vec3(x, 0.5, z), color, glm::vec3(0.2, 0.8, 0.6)));
    }


    // [3n+2 -> 4n+1]
    for (int i = 0; i < n; i++) {
        float x = cos(2 * M_PI / n * i);
        float z = sin(2 * M_PI / n * i);
        vertices.push_back(VertexFormat(glm::vec3(x, -0.5, z), color, glm::vec3(0.2, 0.8, 0.6)));
    }

    vector<unsigned int> indices = vector<unsigned int>();
    for (int i = 1; i < n; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);

        indices.push_back(n + 1);
        indices.push_back(n + 1 + i);
        indices.push_back(n + 1 + i + 1);
    }

    indices.push_back(0);
    indices.push_back(n);
    indices.push_back(1);

    indices.push_back(n + 1);
    indices.push_back(2 * n + 1);
    indices.push_back(n + 2);

    for (int i = 1; i < n; i++) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(2 * n + 1 + i);

        indices.push_back(2 * n + 1 + i);
        indices.push_back(2 * n + 1 + i + 1);
        indices.push_back(i + 1);

        indices.push_back(2 * n + 1 + i);
        indices.push_back(2 * n + 1 + i + 1);
        indices.push_back(3 * n + 1 + i);

        indices.push_back(3 * n + 1 + i);
        indices.push_back(3 * n + 1 + i + 1);
        indices.push_back(2 * n + 1 + i + 1);

        indices.push_back(3 * n + 1 + i);
        indices.push_back(3 * n + 1 + i + 1);
        indices.push_back(n + 1 + i + 1);

        indices.push_back(n + 1 + i);
        indices.push_back(n + 1 + i + 1);
        indices.push_back(3 * n + 1 + i);
    }

    indices.push_back(1);
    indices.push_back(n);
    indices.push_back(3 * n + 1);

    indices.push_back(2 * n + 2);
    indices.push_back(3 * n + 1);
    indices.push_back(1);

    indices.push_back(2 * n + 2);
    indices.push_back(3 * n + 1);
    indices.push_back(4 * n + 1);

    indices.push_back(3 * n + 2);
    indices.push_back(4 * n + 1);
    indices.push_back(2 * n + 2);

    indices.push_back(3 * n + 2);
    indices.push_back(4 * n + 1);
    indices.push_back(2 * n + 1);

    indices.push_back(n + 2);
    indices.push_back(2 * n + 1);
    indices.push_back(3 * n + 2);

    CreateMesh(name, vertices, indices);
}

void Generator::CreateConMesh(const char *name, glm::vec3 color, int vertexCount) {
    int n = vertexCount;

    vector<VertexFormat> vertices = vector<VertexFormat>();

    //  0
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color, glm::vec3(0.2, 0.8, 0.6)));
    //  [1 -> n]
    for (int i = 0; i < n; i++) {
        float x = cos(2 * M_PI / n * i);
        float z = sin(2 * M_PI / n * i);
        vertices.push_back(VertexFormat(glm::vec3(x, 0, z), color, glm::vec3(0.2, 0.8, 0.6)));
    }

    // n + 1
    vertices.push_back(VertexFormat(glm::vec3(0, 1, 0), color, glm::vec3(0.2, 0.8, 0.6)));

    vector<unsigned int> indices = vector<unsigned int>();
    for (int i = 1; i < n; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);

        indices.push_back(n + 1);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(0);
    indices.push_back(n);
    indices.push_back(1);

    indices.push_back(n + 1);
    indices.push_back(n);
    indices.push_back(1);

    CreateMesh(name, vertices, indices);

}

void Generator::CreateGraveStoneMesh(const char *name, glm::vec3 color, int vertexCount) {
    int n = vertexCount;

    vector<VertexFormat> vertices = vector<VertexFormat>();
    // 0
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 1), color, glm::vec3(0.2, 0.8, 0.6)));
    // [1 -> n + 1]
    for (int i = 0; i <= n; i++) {
        float x = cos(M_PI / n * i);
        float y = sin(M_PI / n * i);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 1), color, glm::vec3(0.2, 0.8, 0.6)));
    }

    // n + 2
    vertices.push_back(VertexFormat(glm::vec3(0, 0, -1), color, glm::vec3(0.2, 0.8, 0.6)));
    // [n + 3 -> 2n + 3]
    for (int i = 0; i <= n; i++) {
        float x = cos(M_PI / n * i);
        float y = sin(M_PI / n * i);
        vertices.push_back(VertexFormat(glm::vec3(x, y, -1), color, glm::vec3(0.2, 0.8, 0.6)));
    }

    vector<unsigned int> indices = vector<unsigned int>();
    for (int i = 1; i <= n; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);

        indices.push_back(n + 2);
        indices.push_back(i + n + 2);
        indices.push_back(i + n + 3);

        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + n + 3);

        indices.push_back(i);
        indices.push_back(i + n + 2);
        indices.push_back(i + n + 3);
    }
    cout << vertices.size() << endl;

    // 2n + 4
    vertices.push_back(VertexFormat(glm::vec3(1, -1, 1), color, glm::vec3(0.2, 0.8, 0.6)));
    // 2n + 5
    vertices.push_back(VertexFormat(glm::vec3(-1, -1, 1), color, glm::vec3(0.2, 0.8, 0.6)));

    // 2n + 6
    vertices.push_back(VertexFormat(glm::vec3(1, -1, -1), color, glm::vec3(0.2, 0.8, 0.6)));
    // 2n + 7
    vertices.push_back(VertexFormat(glm::vec3(-1, -1, -1), color, glm::vec3(0.2, 0.8, 0.6)));

    indices.push_back(1);
    indices.push_back(n + 1);
    indices.push_back(2 * n + 5);

    indices.push_back(1);
    indices.push_back(2 * n + 5);
    indices.push_back(2 * n + 4);

    indices.push_back(n + 3);
    indices.push_back(2 * n + 3);
    indices.push_back(2 * n + 7);

    indices.push_back(n + 3);
    indices.push_back(2 * n + 7);
    indices.push_back(2 * n + 6);

    indices.push_back(1);
    indices.push_back(2 * n + 4);
    indices.push_back(2 * n + 6);

    indices.push_back(1);
    indices.push_back(2 * n + 6);
    indices.push_back(n + 3);

    indices.push_back(n + 1);
    indices.push_back(2 * n + 5);
    indices.push_back(2 * n + 7);

    indices.push_back(n + 1);
    indices.push_back(2 * n + 7);
    indices.push_back(2 * n + 3);

    CreateMesh(name, vertices, indices);
}



