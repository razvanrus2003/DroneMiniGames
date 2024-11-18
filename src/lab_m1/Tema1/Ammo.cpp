//
// Created by razvan on 11/9/24.
//

#include "Ammo.h"

#include <iostream>

// Ammo::Ammo(float x, float y, float angle, float init_speed): x_start(x),
//                                                             y_start(y), angle(angle),
//                                                             init_speed(init_speed),
//                                                             acceleration(-0.09),
//                                                             time (0) {}

Ammo::Ammo(float init_speed):init_speed(init_speed),
             acceleration(-0.09),
             time (0) {}

Ammo::~Ammo(){}

glm::mat3 Ammo::getModelMatrix() {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(x, y);
    modelMatrix *= transform2D::Scale(3, 3);
    return modelMatrix;
}

void Ammo::updatePosition(float deltaTimeSeconds) {
    time += deltaTimeSeconds;

    x = x_start + init_speed * cos(angle) * time;
    y = y_start + init_speed * sin(angle) * time + acceleration * time * time / 2;
}


