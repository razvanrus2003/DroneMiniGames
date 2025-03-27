//
// Created by razvan on 12/10/24.
//
#pragma once

#include <iostream>
#include "DroneMain.h"
#include "droneUtil/colors.h"
#include "droneUtil/trasform3d.h"

using namespace transform3D;

namespace m1 {
    class DroneMain;
}

class Drone {
public:
    m1::DroneMain *droneMain;

    Drone(m1::DroneMain *droneMain);

    ~Drone();

    void RenderDrone(glm::mat4 modelMatrix, float time);
    void RenderPropeller(glm::mat4 modelMatrix, float time);
    void RenderMainFrame(glm::mat4 modelMatrix);
};
