//
// Created by razvan on 12/5/24.
//

#include "Sphere.h"
#include <iostream>
#include <utility>

Sphere::Sphere(glm::vec3 center, float radius, glm::mat4 modelMatrix, string mesh_name, string shader_name) {
    this->center = center;

    this->radius = radius;
    this->modelMatrix = modelMatrix;

    this->mesh_name = move(mesh_name);
    this->shader_name = move(shader_name);
}

Sphere::~Sphere() {

}

void Sphere::update(glm::mat4 model) {
    // glm::vec4 center4 = glm::vec4(center, 1.0f);
    // center4 = model * center4;
    // center = glm::vec3(center4.x, center4.y, center4.z);
    //
    // glm::vec4 radius4 = glm::vec4(radius, 0, 0, 0);
    // radius4 = model * radius4;
    // this->radius = radius4.x;
    //
    // modelMatrix = model;
}

void Sphere::update(glm::vec3 center) {
    this->center = center;
}

bool Sphere::checkCollision(Sphere *shape) {
    // return glm::distance(center, shape->center) <= radius + shape->radius;
    return false;
}

bool Sphere::checkCollision(Cube *shape) {
    float angle = shape->angle;

    glm::vec3 cub_center = glm::vec3((shape->minPoint.x + shape->maxPoint.x) / 2,
                           (shape->minPoint.y + shape->maxPoint.y) / 2,
                           (shape->minPoint.z + shape->maxPoint.z) / 2);

    glm::vec3 min_cub = shape->minPoint - cub_center;
    glm::vec3 max_cub = shape->maxPoint - cub_center;

    glm::vec3 sphere_center = center - cub_center;

    min_cub = glm::vec3(min_cub.x * cos(-angle) + min_cub.z * sin(-angle),
                        min_cub.y,
                        -min_cub.x * sin(-angle) + min_cub.z * cos(-angle));
    max_cub = glm::vec3(max_cub.x * cos(-angle) + max_cub.z * sin(-angle),
                        max_cub.y,
                        -max_cub.x * sin(-angle) + max_cub.z * cos(-angle));

    sphere_center = glm::vec3(sphere_center.x * cos(-angle) + sphere_center.z * sin(-angle),
                              sphere_center.y,
                              -sphere_center.x * sin(-angle) + sphere_center.z * cos(-angle));

    const float x = max(min_cub.x, min(sphere_center.x, max_cub.x));
    const float y = max(min_cub.y, min(sphere_center.y, max_cub.y));
    const float z = max(min_cub.z, min(sphere_center.z, max_cub.z));

    const float distance = sqrt((x - sphere_center.x) * (x - sphere_center.x) +
                                (y - sphere_center.y) * (y - sphere_center.y) +
                                (z - sphere_center.z) * (z - sphere_center.z));


    // const float x = max(shape->minPoint.x, min(center.x, shape->maxPoint.x));
    // const float y = max(shape->minPoint.y, min(center.y, shape->maxPoint.y));
    // const float z = max(shape->minPoint.z, min(center.z, shape->maxPoint.z));
    //
    // const float distance = sqrt((x - center.x) * (x - center.x) +
    //                             (y - center.y) * (y - center.y) +
    //                             (z - center.z) * (z - center.z));

    return distance <= radius;
}

bool Sphere::checkCollision(glm::vec3 point) {
    // return glm::distance(point, center) <= radius;
    return false;
}