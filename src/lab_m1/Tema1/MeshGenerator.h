//
// Created by razvan on 11/7/24.
//

#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include "colors.h"
#include "components/simple_scene.h"

using namespace m1;
using namespace std;

class MeshGenerator {
    public:

    // MeshGenerator();

    MeshGenerator(unordered_map<std::string, Mesh *> &meshes);

    ~MeshGenerator();

    void CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);
    void CreateBaseSquareMesh();
    void CreateTracksMesh();
    void CreateMainTankDesertYellowBoxMesh();
    void CreateDesertYellowSemiCircleMesh();
    void CreateMainTankCamoGreenBoxMesh();
    void CreateCamoGreenCircleMesh();
    void CreateCannonMesh();
    void CreateCircleMesh();
    void CreateWhiteCircleMesh();
    void CreateHealthSquare(glm::vec3 color, const char* name);
    std::unordered_map<std::string, Mesh *> &meshes;

};

