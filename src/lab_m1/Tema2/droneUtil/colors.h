//
// Created by razvan on 11/6/24.
//

#pragma once

#include "utils/glm_utils.h"

namespace m1
{
    const float SKY_R = (float)160/255;
    const float SKY_G = (float)160/255;
    const float SKY_B = (float)160/255;

    const float TERRAIN_R = (float)255/255;
    const float TERRAIN_G = (float)255/255;
    const float TERRAIN_B = (float)151/255;

    const float GRASS_R = (float)0/255;
    const float GRASS_G = (float)102/255;
    const float GRASS_B = (float)0/255;

    const float DIRT_R = (float)102/255;
    const float DIRT_G = (float)51/255;
    const float DIRT_B = (float)0/255;

    const float STONE_R = (float)64/255;
    const float STONE_G = (float)64/255;
    const float STONE_B = (float)64/255;

    const float FOG_R = (float)160/255;
    const float FOG_G = (float)160/255;
    const float FOG_B = (float)160/255;

    const float DRONE_R = (float)16/255;
    const float DRONE_G = (float)16/255;
    const float DRONE_B = (float)16/255;

    const float DRONE_PROP_R = (float)51/255;
    const float DRONE_PROP_G = (float)0/255;
    const float DRONE_PROP_B = (float)51/255;

    const float HitBox_R = (float)236/255;
    const float HitBox_G = (float)44/255;
    const float HitBox_B = (float)5/255;

    const float TRUNK_R = (float)40/255;
    const float TRUNK_G = (float)7/255;
    const float TRUNK_B = (float)7/255;

    inline glm::vec3 terrain_color() {
        return {TERRAIN_R, TERRAIN_G, TERRAIN_B};
    }

    inline glm::vec3 stone_color() {
        return {STONE_R, STONE_G, STONE_B};
    }

    inline glm::vec3 grass_color() {
        return {GRASS_R, GRASS_G, GRASS_B};
    }

    inline glm::vec3 sky_color() {
        return {SKY_R, SKY_G, SKY_B};
    }

    inline glm::vec3 dirt_color() {
        return {DIRT_R, DIRT_G, DIRT_B};
    }

    inline glm::vec3 fog_color() {
        return {FOG_R, FOG_G, FOG_B};
    }

    inline glm::vec3 drone_color() {
        return {DRONE_R, DRONE_G, DRONE_B};
    }

    inline glm::vec3 drone_prop_color() {
        return {DRONE_PROP_R, DRONE_PROP_G, DRONE_PROP_B};
    }

    inline glm::vec3 hitBox_color() {
        return {HitBox_R, HitBox_G, HitBox_B};
    }

    inline glm::vec3 trunk_color() {
        return {TRUNK_R, TRUNK_G, TRUNK_B};
    }

}  // namespace m1
