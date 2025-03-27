//
// Created by razvan on 11/7/24.
//

#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include "droneUtil/colors.h"
#include "components/simple_scene.h"


using namespace m1;
using namespace std;

class Generator {
    public:

    // MeshGenerator();
    std::unordered_map<std::string, Mesh *> &meshes;
    std::unordered_map<std::string, Shader *> &shaders;

    explicit Generator(unordered_map<std::string, Mesh *> &meshes, unordered_map<std::string, Shader *> &shaders);

    ~Generator();

    void CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);
    void CreateTerrainMesh(const char *name, glm::vec3 color, int vertexCount);
    void CreateCubeMesh(const char *name, glm::vec3 color);
    void CreateCylinderMesh(const char *name, glm::vec3 color, int vertexCount);
    void CreateConMesh(const char *name, glm::vec3 color, int vertexCount);
    void CreateGraveStoneMesh(const char *name, glm::vec3 color, int vertexCount);

    void CreateShader(string window_path, const char *name, const char *vertexShader, const char *fragmentShader);

};

