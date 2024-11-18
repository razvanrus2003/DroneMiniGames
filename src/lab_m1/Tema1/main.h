//
// Created by razvan on 11/5/24.
//

#pragma once

#include "components/simple_scene.h"
#include "colors.h"
#include "MeshGenerator.h"
#include <vector>
#include <iostream>
#include <string>
#include "tank.h"
#include "transform2D.h"
using namespace std;


namespace m1
{
    class Main : public gfxc::SimpleScene
    {
    public:
        Main();
        ~Main();

        void Init() override;

    private:
        void InitCameraPosition();

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // Class variables go here
        glm::ivec2 resolution;

        vector<float> terrain_y;
        vector<float> terrain_x;

        vector<float> terrain_amplitude = {0.1, 2, 1, 0.3f, 0.7f};
        vector<float> terrain_frequency = {1, 2.4f, 0.7, 0.7f, 0.4f};

        float terrain_small_threshold = 0.3;
        float terrain_small_transfer = 0.05;

        float terrain_large_threshold = 5;
        float terrain_large_transfer = 1;

        float terrain_angle_threshold;

        bool showHitBox = false;
        bool dronestrike = false;

        float terrain_pixel_frequency = 1;

        MeshGenerator meshGenerator;
        glm::mat3 modelMatrix;

        Tank tankA;
        Tank tankB;
        protected:
            GLenum cullFace;
            GLenum polygonMode;
    };
}   // namespace m1
