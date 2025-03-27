//
// Created by razvan on 12/5/24.
//

#pragma once
#include <vector>
#include "Sphere.h"
#include "utils/glm_utils.h"
#include "string"
#include "iostream"
#include "../../droneUtil/trasform3d.h"

using namespace transform3D;
using namespace std;
class Sphere;

class Cube {
public:
    glm::vec3 minPoint;
    glm::vec3 maxPoint;

    vector<glm::vec4> points;

    glm::mat4 modelMatrix;
    string mesh_name;
    string shader_name;
    float angle;

    Cube(glm::vec3 minPoint, glm::vec3 maxPoint, glm::mat4 modelMatrix, string mesh_name, string shader_name, float rand);
    ~Cube();

    void update(glm::mat4 model);


    bool checkCollision(glm::vec3 point);

    bool checkCollision(Cube *shape);
    bool checkCollision(Sphere *shape);

    glm::mat4 getHitBoxModelMatrix();
};

