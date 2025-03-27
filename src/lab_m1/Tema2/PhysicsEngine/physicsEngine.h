//
// Created by razvan on 12/5/24.
//
#pragma once
#include <vector>

#include "Shapes/Sphere.h"
#include "Shapes/Cube.h"
#include "../Terrain.h"
#include "Shapes/DroneHitBox.h"

class DroneHitBox;
namespace m1 {
    class DroneMain;
}
class physicsEngine {
public:
    physicsEngine();
    ~physicsEngine();

    std::vector<Cube *> static_shapes;
    Cube *terrain_shape;
    Terrain terrain;

    void addShape(Cube* shape);
    void addTerrain(Cube* shape, Terrain& terrain);

    bool checkCollisionWithEnv(DroneHitBox* hitBox);

};
