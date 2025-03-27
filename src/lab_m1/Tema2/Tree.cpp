//
// Created by razvan on 12/14/24.
//

#include "Tree.h"

Tree::Tree(glm::vec3 position, float trunk_height, float trunk_radius, m1::DroneMain *droneMain) {
    this->position = position;
    this->trunk_height = trunk_height;
    this->trunk_radius = trunk_radius;
    this->droneMain = droneMain;
}

void Tree::RenderRest(mat4 modelMatrix, int lvl, vec4 scale) {
    if (lvl == 0) {
        return;
    }
    float angleX = M_PI / 12;
    float angleY = 0;
    for (int i = 1; i <= 3; i++) {
        angleY = i * M_PI / 6;
        // modelMatrix *= Scale()
        // modelMatrix *= RotateOY(angleY);
        // modelMatrix *= RotateOX(angleX);
        modelMatrix *= Scale(scale.x / scale.x, 0.5 * scale.z/ scale.y, 2 * scale.y / scale.z);
        modelMatrix *= Scale(0.8, 0.7, 0.8);
        modelMatrix *= Translate(.5, 2, .5);
        droneMain->RenderMesh("Cube", "Normal", modelMatrix, trunk_color() + vec3(lvl % 2 == 1, 0, 0), trunk_color());

        modelMatrix *= Translate(0.2, 0.3, 0.2);
        vec4 newScale = vec4(scale.x, scale.y, scale.z, 1);
        // float aux = newScale.y;
        // newScale.y = newScale.z;
        // newScale.z = aux;
        modelMatrix *= Scale(1 / newScale.x, 1 / newScale.y, 1 / newScale.z);

        RenderRest(modelMatrix, lvl - 1, newScale);
    }
}

void Tree::RenderMainTrunk(mat4 modelMatrix) {

    mat4 modelMatrix2 = modelMatrix * Scale(trunk_radius, trunk_height, trunk_radius);
    modelMatrix2 *= Translate(0, 1, 0);
    droneMain->RenderMesh("Cube", "Normal", modelMatrix2, trunk_color(), trunk_color());

    vec4 scale = vec4(trunk_radius, trunk_height,  trunk_radius, 1);
    modelMatrix *= Translate(0, trunk_height, 0);
    modelMatrix *= Scale(10, 10, 10);
    RenderRest(modelMatrix, 3, scale);
}

void Tree::Render() {
    mat4 modelMatrix2 = mat4(1);

    modelMatrix2 *= Translate(position.x, (position.y), position.z);
    modelMatrix2 *= Scale(1, 1, 1);
    int lvl = 3;
    RenderMainTrunk(modelMatrix2);
}
