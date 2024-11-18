//
// Created by razvan on 11/7/24.
//
#pragma once
#include <vector>
#include <algorithm>
#include <cmath>

#include "Ammo.h"
#include "utils/glm_utils.h"
#include "transform2D.h"

using namespace std;

class Tank {
    public:
    Tank(float &terrain_pixel_frequency, vector<float> &terrain_x, vector<float> &terrain_y);
    ~Tank();

    float &terrain_pixel_frequency;
    vector<float> &terrain_x;
    vector<float> &terrain_y;
    float ySubtract = 5.0f;
    float health;

    float x, y, angle, cannonAngle;
    float ammo_x, ammo_y, ammo_angle;
    float fireCooldown;
    bool alive = true;

    float TankY(float tank_x);
    float TankAngle(float tank_x);

    bool flyingAmmo = false;
    vector<Ammo> shells;

    glm::mat3 TracksMatrix();
    glm::mat3 BodyMatrix();
    glm::mat3 TurretMatrix();
    glm::mat3 CannonMatrix();
    glm::mat3 HealthMatrix();
    glm::mat3 HealthFrameMatrix();


    void ShootAmmo();
    void UpdateAmmoPos(float deltaTimeSeconds, Tank &enemy);

    float predX(float t, float xx, float a);

    float predY(float t, float yy, float a);

    glm::mat3 getPredMatrix(float xx, float yy);
};

