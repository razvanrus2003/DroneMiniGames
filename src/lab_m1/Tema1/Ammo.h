//
// Created by razvan on 11/9/24.
//

#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include "utils/glm_utils.h"
#include "transform2D.h"

using namespace std;

class Ammo {
    public:
        float x, y, angle;
        float acceleration;
        float init_speed;
        float time;
        float x_start, y_start;

    // Ammo(float x, float y, float angle, float init_speed);

    Ammo(float init_speed);

    ~Ammo();

    glm::mat3 getModelMatrix();
    void updatePosition(float deltaTimeSeconds);
};
