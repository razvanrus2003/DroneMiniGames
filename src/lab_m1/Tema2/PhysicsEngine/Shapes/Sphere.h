//
// Created by razvan on 12/5/24.
//
#pragma once
#include "Cube.h"
#include "utils/glm_utils.h"
#include "string"

using namespace std;
class Cube;


class Sphere {
public:
    glm::vec3 center;
    float radius;

    glm::mat4 modelMatrix;
    string mesh_name;
    string shader_name;

    Sphere(glm::vec3 center, float radius, glm::mat4 modelMatrix, string mesh_name,  string shader_name);
    ~Sphere();

    void update(glm::mat4 model) ;
    void update(glm::vec3 center) ;

    bool checkCollision(glm::vec3 point) ;

    bool checkCollision(Sphere* shape);
    bool checkCollision(Cube* shape);
};

