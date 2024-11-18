//
// Created by razvan on 11/7/24.
//

#include "tank.h"

#include <iostream>

Tank::Tank(float &terrain_pixel_frequency, vector<float> &terrain_x, vector<float> &terrain_y):
    terrain_pixel_frequency(terrain_pixel_frequency),
    terrain_x(terrain_x),
    terrain_y(terrain_y),
    shells(vector<Ammo>()),
    fireCooldown(0),
    health(100){}

Tank::~Tank() {

}

float Tank::TankY(float tank_x) {
    int A = floor(tank_x / terrain_pixel_frequency);
    int B = ceil(tank_x / terrain_pixel_frequency);

    if (A == B) {
        A--;
    }

    float t = (tank_x - terrain_x[A]) / (terrain_x[B] - terrain_x[A]);
    return terrain_y[A] + t * (terrain_y[B] - terrain_y[A]) - ySubtract;
}

float Tank::TankAngle(float tank_x) {
    int A = floor(tank_x / terrain_pixel_frequency);
    int B = ceil(tank_x / terrain_pixel_frequency);

    if (A == B) {
        A--;
    }
    if (A == -1) {
        A = 0;
        B = 1;
    }

    return atan2((terrain_y[B] - terrain_y[A]), (terrain_x[B] - terrain_x[A]));
}

glm::mat3 Tank::TracksMatrix() {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(x, y);

    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Scale(20, 15);

    return modelMatrix;
}
glm::mat3 Tank::BodyMatrix() {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(x - 14.0 * sin(angle), y + 14.0 * cos(angle));

    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Scale(25, 20);

    return modelMatrix;
}

glm::mat3 Tank::TurretMatrix() {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(x - 34.0 * sin(angle), y + 34.0 * cos(angle));

    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Scale(20, 20);
    return modelMatrix;
}

glm::mat3 Tank::CannonMatrix() {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(x - 34.0 * sin(angle), y + 34.0 * cos(angle));

    modelMatrix *= transform2D::Rotate(cannonAngle);
    modelMatrix *= transform2D::Translate(19 * cos(angle), 19 * sin(angle));

    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Scale(40, 4);
    return modelMatrix;
}

void Tank::ShootAmmo() {
    Ammo newAmmo = Ammo(7);
    newAmmo.time = 0;
    newAmmo.x_start = ammo_x;
    newAmmo.y_start = ammo_y;
    newAmmo.angle = ammo_angle;
    shells.push_back(newAmmo);

    fireCooldown = 5;
    flyingAmmo = true;
}

void Tank::UpdateAmmoPos(float deltaTimeSeconds, Tank &enemy) {
    ammo_x = x - 34.0 * sin(angle) + 55 * cos(cannonAngle + angle);
    ammo_y = y + 34.0 * cos(angle) + 55 * sin(cannonAngle + angle);
    ammo_angle = angle + cannonAngle;
    if (fireCooldown > 0) {
        fireCooldown -= deltaTimeSeconds / 10;
        if (fireCooldown < 0) {
            fireCooldown = 0;
        }
    }

    if (flyingAmmo == true) {
        for (int i = 0; i < shells.size(); i++) {
            shells[i].updatePosition(deltaTimeSeconds);
            Ammo ammo = shells[i];

            int A = floor(ammo.x / terrain_pixel_frequency);
            int B = ceil(ammo.x / terrain_pixel_frequency);

            if (A == B) {
                A--;
            }
            if (A == -1) {
                A = 0;
                B = 1;
            }

            float t = (ammo.x - terrain_x[A]) / (terrain_x[B] - terrain_x[A]);
            float I_x = terrain_x[A] * (1 - t) + terrain_x[B] * t;
            float I_y = terrain_y[A] * (1 - t) + terrain_y[B] * t;
            if (ammo.x < 0) {
                shells.erase(shells.begin() + i);
                if (shells.size() == 0) {
                    flyingAmmo = false;
                }
            }
            float eHit_x = (enemy.x - ammo.x - 24.0 * sin(enemy.angle)) * cos(-enemy.angle) - (enemy.y - ammo.y + 24.0*cos(enemy.angle)) * sin(-enemy.angle);
            float eHit_y = (enemy.x - ammo.x - 24.0 * sin(enemy.angle)) * sin(-enemy.angle) + (enemy.y - ammo.y + 24.0*cos(enemy.angle)) * cos(-enemy.angle);

            float myHit_x = (x - ammo.x - 24.0 * sin(angle)) * cos(-angle) - (y - ammo.y + 24.0*cos(angle)) * sin(-angle);
            float myHit_y = (x - ammo.x - 24.0 * sin(angle)) * sin(-angle) + (y - ammo.y + 24.0*cos(angle)) * cos(-angle);

            if (enemy.alive && pow(eHit_x/2.4, 2) + pow(eHit_y/1.4, 2) < 400) {
                enemy.health -= 4 * abs(rand() % 5);
                cout << "Hit!! "  << "Remaing health " << enemy.health  << "\n";

                shells.erase(shells.begin() + i);
                if (shells.size() == 0) {
                    flyingAmmo = false;
                }
            } else if (pow(myHit_x/2, 2) + pow(myHit_y/1.2, 2) < 400) {
                health -= 4 * abs(rand() % 5);
                cout << "SelfHit!! "  << "Remaing health " << health  << "\n";
                shells.erase(shells.begin() + i);
                if (shells.size() == 0) {
                    flyingAmmo = false;
                }
            } else if (ammo.y - I_y < 5) {
                shells.erase(shells.begin() + i);
                if (shells.size() == 0) {
                    flyingAmmo = false;
                }
                cout << "Terrain hit!\n";
                int A_0 = A, B_0 = B;
                for (int i = 0 ; I_x - terrain_x[A] < 20 && terrain_x[B] - I_x < 20; i ++) {
                    // terrain_y[A] = I_y - sin(acos((I_x - terrain_x[A]) / 20 )) * 20;
                    if (terrain_y[A] >= I_y - sin(acos((terrain_x[B] - I_x) / 20 )) * 20 && A >= 0 ) {
                        terrain_y[A] = I_y - sin(acos((I_x - terrain_x[A]) / 20 )) * 20;
                    }
                    // terrain_y[B] = I_y - sin(acos((terrain_x[B] - I_x) / 20 )) * 20;
                    if (terrain_y[B] >= I_y - sin(acos((terrain_x[B] - I_x) / 20 )) * 20 && B < terrain_x.size() ) {
                        terrain_y[B] = I_y - sin(acos((terrain_x[B] - I_x) / 20 )) * 20;
                    }
                    A--;
                    B++;
                }
            }
        }
    }
}

float Tank::predX(float t, float xx, float a) {
    return ammo_x + 7 * cos(ammo_angle) * t;
}

float Tank::predY(float t, float yy, float a) {
    return ammo_y + 7 * sin(ammo_angle) * t -0.09 * t * t / 2;
}

glm::mat3 Tank::getPredMatrix(float xx, float yy) {
    glm::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(xx, yy);
    modelMatrix *= transform2D::Scale(1.5f, 1.5f);
    return modelMatrix;
}

glm::mat3 Tank::HealthMatrix() {
    glm ::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(x - 70.0 * sin(angle) -30 * cos(angle) , y + 70.0 * cos(angle) - 30 *sin(angle));

    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Scale(60.0 * health / 100,
        5);
    return modelMatrix;
}

glm::mat3 Tank::HealthFrameMatrix() {
    glm ::mat3 modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(x - 62.0 * sin(angle) -33 * cos(angle) , y +62.0 * cos(angle) - 33 *sin(angle));

    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Scale(66.0, -11);
    return modelMatrix;
}


