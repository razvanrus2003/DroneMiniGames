//
// Created by razvan on 12/5/24.
//

#include "Cube.h"
#include <utility>

Cube::Cube(glm::vec3 minPoint, glm::vec3 maxPoint, glm::mat4 modelMatrix, string mesh_name, string shader_name, float rand) {
    this->minPoint = glm::vec4(minPoint, 1);
    this->maxPoint = glm::vec4(maxPoint, 1);

    this->angle = ((int)rand % 5) * M_PI / 30;

    this->maxPoint.y *= abs(sin(rand))*.5 + .4;
    this->maxPoint.y += abs(sin(rand)) * 0.2;

    // this->minPoint.z += glm::sign(this->minPoint.z) * abs(sin(rand) * 0.7);
    // this->minPoint.y *= abs(sin(rand))*.5 + 1;
    // this->minPoint.x += glm::sign(this->minPoint.x) * abs(sin(rand) * 0.2);

    this->modelMatrix = modelMatrix;
    this->points = vector<glm::vec4>(8);

    this->points[0] = modelMatrix * glm::vec4(minPoint.x, minPoint.y, minPoint.z, 1.0f);
    this->points[1] = modelMatrix * glm::vec4(maxPoint.x, minPoint.y, minPoint.z, 1.0f);
    this->points[2] = modelMatrix * glm::vec4(maxPoint.x, this->maxPoint.y, minPoint.z, 1.0f);
    this->points[3] = modelMatrix * glm::vec4(minPoint.x, this->maxPoint.y, minPoint.z, 1.0f);
    this->points[4] = modelMatrix * glm::vec4(minPoint.x, minPoint.y, maxPoint.z, 1.0f);
    this->points[5] = modelMatrix * glm::vec4(maxPoint.x, minPoint.y, maxPoint.z, 1.0f);
    this->points[6] = modelMatrix * glm::vec4(minPoint.x, this->maxPoint.y, maxPoint.z, 1.0f);
    this->points[7] = modelMatrix * glm::vec4(maxPoint.x, this->maxPoint.y, maxPoint.z, 1.0f);

    this->minPoint = modelMatrix * glm::vec4(this->minPoint, 1);
    this->maxPoint = modelMatrix * glm::vec4(this->maxPoint, 1);

    // if (this->minPoint.x > this->maxPoint.x) {
    //     float aux = this->minPoint.x;
    //     this->minPoint.x = this->maxPoint.x;
    //     this->maxPoint.x = aux;
    // }
    //
    // if (this->minPoint.z > this->maxPoint.z) {
    //     float aux = this->minPoint.z;
    //     this->minPoint.z = this->maxPoint.z;
    //     this->maxPoint.z = aux;
    // }

    this->mesh_name = std::move(mesh_name);
    this->shader_name = std::move(shader_name);
}

Cube::~Cube() {

}

void Cube::update(glm::mat4 model) {

}
bool Cube::checkCollision(Cube *shape) {
    // return minPoint.x <= shape->maxPoint.x && maxPoint.x >= shape->minPoint.x &&
    //        minPoint.y <= shape->maxPoint.y && maxPoint.y >= shape->minPoint.y &&
    //        minPoint.z <= shape->maxPoint.z && maxPoint.z >= shape->minPoint.z;
    return false;
}

bool Cube::checkCollision(Sphere *shape) {
    // const float x = max(minPoint.x, min(shape->center.x, maxPoint.x));
    // const float y = max(minPoint.y, min(shape->center.y, maxPoint.y));
    // const float z = max(minPoint.z, min(shape->center.z, maxPoint.z));
    //
    // const float distance = sqrt((x - shape->center.x) * (x - shape->center.x) +
    //                             (y - shape->center.y) * (y - shape->center.y) +
    //                             (z - shape->center.z) * (z - shape->center.z));
    //
    // return distance < shape->radius;
    return false;
}

bool Cube::checkCollision(glm::vec3 point) {
    // return point.x >= minPoint.x && point.x <= maxPoint.x &&
    //        point.y >= minPoint.y && point.y <= maxPoint.y &&
    //        point.z >= minPoint.z && point.z <= maxPoint.z;
    return false;
}

glm::mat4 Cube::getHitBoxModelMatrix() {
    glm::vec3 center = (minPoint + maxPoint) / 2.0f;

    glm::mat4 modelMatrix = glm::mat4(1);

    glm::vec3 min_cub = minPoint - center;
    glm::vec3 max_cub = maxPoint - center;

    min_cub = glm::vec3(min_cub.x * cos(angle) - min_cub.z * sin(angle),
                        min_cub.y,
                        min_cub.x * sin(angle) + min_cub.z * cos(angle));
    max_cub = glm::vec3(max_cub.x * cos(angle) - max_cub.z * sin(angle),
                        max_cub.y,
                        max_cub.x * sin(angle) + max_cub.z * cos(angle));

    modelMatrix *= Translate(center.x, center.y, center.z);
    modelMatrix *= RotateOY(angle);
    modelMatrix *= Scale((max_cub.x - min_cub.x) / 2, (max_cub.y - min_cub.y) / 2, (max_cub.z - min_cub.z) / 2);


    return modelMatrix;
}
