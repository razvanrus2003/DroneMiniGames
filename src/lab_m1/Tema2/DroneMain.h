//
// Created by razvan on 12/1/24.
//

#pragma once

#include "Drone.h"
#include "components/simple_scene.h"
#include "Generator.h"
#include "Terrain.h"
#include "droneUtil/trasform3d.h"
#include "PhysicsEngine/physicsEngine.h"
#include "PhysicsEngine/Shapes/DroneHitBox.h"
#include "Tree.h"
using namespace transform3D;

using namespace std;

class Tree;
class Drone;
class DroneHitBox;
class physicsEngine;

namespace m1
{
    class DroneMain : public gfxc::SimpleScene
    {
    public:
        DroneMain();
        ~DroneMain();

        void Init() override;

        // Class variables go here
        glm::ivec2 resolution;
        Generator generator;

        Terrain terrain = Terrain(600, vec3(10, 4, 10), 0.004);

        physicsEngine* physics_engine;
        vector<Cube *> shapes;
        vector<float> graves_init = vector<float>();

        DroneHitBox* drone_hitBox;
        glm::vec3 drone_position = glm::vec3(2000, 150, 2000);
        glm::vec3 drone_rotating = glm::vec3(0, 4, 0);

        glm::vec3 drone_model_rot = glm::vec3(0, M_PI / 4, 0);
        Drone* drone;
        glm::vec3 camera_rotation = glm::vec3(-0.2, 0, 0);
        glm::vec3 camera_distances = glm::vec3(0, 0, 15);
        Tree *tree;
        bool show_hitBox = false;
        float time = 0;

        bool collision = false;
        void RenderMesh(string mesh, const glm::mat4 & modelMatrix, const glm::vec3 &color);
        void RenderMesh(string mesh, string shader, const glm::mat4 & modelMatrix, const glm::vec3 &color1, const glm::vec3 &color2);
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

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color1, const glm::vec3 &color2, const float resolution);
        void RenderMesh(Mesh *mesh, const glm::mat4 & modelMatrix, const glm::vec3 &color);
    };
}   // namespace m1



