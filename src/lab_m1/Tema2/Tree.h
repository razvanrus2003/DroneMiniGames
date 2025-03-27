//
// Created by razvan on 12/14/24.
//
#pragma once
#include "DroneMain.h"
#include "utils/glm_utils.h"
#include "iostream"
#include "droneUtil/trasform3d.h"

namespace m1 {
    class DroneMain;
}

class Tree {
public:
    glm::vec3 position;
    float trunk_height;
    float trunk_radius;
    m1::DroneMain *droneMain;

    Tree(glm::vec3 position, float trunk_height, float trunk_radius, m1::DroneMain *droneMain);

    void Render();
    void RenderRest(mat4 modelMatrix, int lvl, vec4 scale);
    void RenderMainTrunk(mat4 modelMatrix);
};
