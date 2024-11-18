//
// Created by razvan on 11/6/24.
//

#pragma once

#include "utils/glm_utils.h"

namespace m1
{
    const float SKY_R = (float)51/255;
    const float SKY_G = (float)153/255;
    const float SKY_B = (float)255/255;

    const float TERRAIN_R = (float)255/255;
    const float TERRAIN_G = (float)255/255;
    const float TERRAIN_B = (float)151/255;

    const float TRACKS_R = (float)140/255;
    const float TRACKS_G = (float)142/255;
    const float TRACKS_B = (float)88/255;

    const float BODY_YELLOW_R = (float)202/255;
    const float BODY_YELLOW_G = (float)141/255;
    const float BODY_YELLOW_B = (float)22/255;

    const float BODY_GREEN_R = (float)120/255;
    const float BODY_GREEN_G = (float)134/255;
    const float BODY_GREEN_B = (float)107/255;

    const float AMMO_R = (float)64/255;
    const float AMMO_G = (float)64/255;
    const float AMMO_B = (float)64/255;

    const float PREAD_R = (float)255/255;
    const float PREAD_G = (float)255/255;
    const float PREAD_B = (float)255/255;

    const float HEALTH_R = (float)255/255;
    const float HEALTH_G = (float)0/255;
    const float HEALTH_B = (float)255/255;

    const float FRAME_R = (float)102/255;
    const float FRAME_G = (float)0/255;
    const float FRAME_B = (float)102/255;

    inline glm::vec3 terrain_color() {
        return {TERRAIN_R, TERRAIN_G, TERRAIN_B};
    }

    inline glm::vec3 tracks_color() {
        return {TRACKS_R, TRACKS_G, TRACKS_B};
    }

    inline glm::vec3 tank_body_yellow_color() {
        return {BODY_YELLOW_R, BODY_YELLOW_G, BODY_YELLOW_B};
    }

    inline glm::vec3 tank_body_green_color() {
        return {BODY_GREEN_R, BODY_GREEN_G, BODY_GREEN_B};
    }

    inline glm::vec3 ammo_color() {
        return {AMMO_R, AMMO_G, AMMO_B};
    }

    inline glm::vec3 pread_color() {
        return {PREAD_R, PREAD_G, PREAD_B};
    }

    inline  glm::vec3 health() {
        return {HEALTH_R, HEALTH_G, HEALTH_B};
    }

    inline glm::vec3 frame() {
        return {FRAME_R, FRAME_G, FRAME_B};
    }
}  // namespace m1
