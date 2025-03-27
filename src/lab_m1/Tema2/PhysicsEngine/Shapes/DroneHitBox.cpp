//
// Created by razvan on 12/14/24.
//

#include "DroneHitBox.h"

DroneHitBox::DroneHitBox(glm::vec3 center, float radius, DroneMain *droneMain) {
    this->center = center;
    this->radius = radius;
    this->hitBoxes = std::vector<Sphere *>();
    this->droneMain = droneMain;

    for (int i = 0; i < 4; i++) {
        float angle = i * M_PI / 2;
        glm::vec3 point = glm::vec3(cos(angle) * armLength + center.x, center.y + 1, center.z + sin(angle) * armLength);

        Sphere *hitBox = new Sphere(point, radius, glm::mat4(1), "sphere", "HitBox");
        hitBoxes.push_back(hitBox);
    }
}

void DroneHitBox::update(glm::vec3 position, float drone_rotation) {
    center = position;
    for (int i = 0; i < 4; i++) {
        float angle = i * M_PI / 2;
        glm::vec3 point = glm::vec3(cos(angle - drone_rotation) * armLength + center.x, center.y + 1, center.z + sin(angle - drone_rotation) * armLength);
        hitBoxes[i]->update(point);
    }
}

void DroneHitBox::Render(glm::mat4 modelMatrix) {
    for (int i = 0; i < 4; i++) {
        float angle = i * M_PI / 2;

        glm::mat4 modelMatrix2 = mat4(1);
        // modelMatrix2 *= Translate(cos(angle) * armLength, 1, sin(angle) * armLength);
        modelMatrix2 *= Translate(hitBoxes[i]->center.x, hitBoxes[i]->center.y, hitBoxes[i]->center.z);
        modelMatrix2 *= Scale(radius * 2, radius * 2, radius * 2);
        droneMain->RenderMesh("sphere", "HitBox", modelMatrix2, hitBox_color(), hitBox_color());
    }
}
