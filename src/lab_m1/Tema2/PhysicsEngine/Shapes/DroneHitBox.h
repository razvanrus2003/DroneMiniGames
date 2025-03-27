//
// Created by razvan on 12/14/24.
//

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Sphere.h"
#include "lab_m1/Tema2/DroneMain.h"
#include "utils/glm_utils.h"

namespace m1 {
    class DroneMain;
}
class DroneHitBox {
public:
    std::vector<Sphere *> hitBoxes;
    glm::vec3 center;
    float radius;
    float armLength = 7.6;

    DroneMain *droneMain;
    DroneHitBox(glm::vec3 center, float radius, DroneMain *droneMain);

    void Render(glm::mat4 modelMatrix);

    void update(glm::vec3 position, float drone_rotation);
};
