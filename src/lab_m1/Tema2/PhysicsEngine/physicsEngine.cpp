//
// Created by razvan on 12/5/24.
//

#include "physicsEngine.h"
#include <iostream>

physicsEngine::physicsEngine() {
    this->static_shapes = std::vector<Cube *>();
}

physicsEngine::~physicsEngine() {

}

void physicsEngine::addTerrain(Cube *shape, Terrain &terrain) {
    this->terrain = terrain;
    this->terrain_shape = shape;
}


void physicsEngine::addShape(Cube* shape) {
    static_shapes.push_back(shape);
}

bool physicsEngine::checkCollisionWithEnv(DroneHitBox* hitBox) {

    vec3 center = hitBox->center;
    float y_noise = terrain.getHeights(center.x, center.z);

    if (center.y - hitBox->radius < y_noise) {
        cout << "Terrain collision" << " " << y_noise << "  " << center.y << endl;
        return true;
    }

    for (Cube * shape : static_shapes) {
        int i = 0;
        for (Sphere * sphere : hitBox->hitBoxes) {
            if (sphere->checkCollision(shape)) {
                cout << sphere->center << endl;
                cout << i <<endl;
                return true;
            }
            i++;
        }
    }
    return false;
}








