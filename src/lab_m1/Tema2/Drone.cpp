//
// Created by razvan on 12/10/24.
//

#include "Drone.h"

Drone::Drone(DroneMain *droneMain) {
    this->droneMain = droneMain;
}
Drone::~Drone() {
}

void Drone::RenderDrone(glm::mat4 modelMatrix, float time) {
    RenderMainFrame(modelMatrix);
    RenderPropeller(modelMatrix, time);
}

void Drone::RenderPropeller(glm::mat4 modelMatrix, float time) {
    glm::mat4 aux_mat;
    for (int i = 1; i <= 4; i++) {
        aux_mat = modelMatrix;
        aux_mat *= RotateOY(M_PI / 2 * i);
        aux_mat *= Translate(8, 0, 0);
        aux_mat *= Scale(1.5, 3, 1.5);
        droneMain->RenderMesh("Cylinder", "Propeller", aux_mat, drone_color(), drone_prop_color());

        aux_mat = modelMatrix;
        aux_mat *= RotateOY(M_PI / 2 * i);
        aux_mat *= Translate(8, 3.1, 0);
        aux_mat *= RotateOY(time * 20 * M_PI);
        aux_mat *= Scale(3, .05, .12);
        // aux_mat *= Translate(1, 0, 0);
        droneMain->RenderMesh("Cube", "Normal", aux_mat, drone_color(), drone_color());

        aux_mat = modelMatrix;
        aux_mat *= RotateOY(M_PI / 2 * i);
        aux_mat *= Translate(8, 3, 0);
        aux_mat *= Scale(0.5, 0.6, 0.5);
        droneMain->RenderMesh("Cylinder", "Con", aux_mat, drone_color(), drone_color());
    }

    for (int i = 1; i <= 4; i++) {
        aux_mat = modelMatrix;
        aux_mat *= RotateOY(M_PI / 2 * i);
        aux_mat *= Translate(8, 3.1, 0);
        aux_mat *= Scale(3.1, 0.05, 3.1);
        droneMain->RenderMesh("Cylinder", "Rotor", aux_mat, drone_color(), drone_color());
    }
}

void Drone::RenderMainFrame(glm::mat4 modelMatrix) {
    glm::mat4 aux_mat = modelMatrix;

    aux_mat *= Scale(8, 1, 1);
    droneMain->RenderMesh("Cube", aux_mat, drone_color());

    aux_mat = modelMatrix;
    aux_mat *= RotateOY(M_PI / 2);
    aux_mat *= Scale(8, 1, 1);
    droneMain->RenderMesh("Cube", aux_mat, drone_color());

    aux_mat = modelMatrix;
    aux_mat *= RotateOY(M_PI / 4);
    aux_mat *= Scale(3, 1.5, 3);
    droneMain->RenderMesh("Cube", aux_mat, drone_prop_color());

    aux_mat = modelMatrix;
    aux_mat *= RotateOY(M_PI / 4);
    aux_mat *= Scale(2.5, 1.7, 2.5);
    droneMain->RenderMesh("Cube", aux_mat, drone_color());
}