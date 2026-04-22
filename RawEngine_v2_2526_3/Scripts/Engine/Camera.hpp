#pragma once

#include "GameObject.hpp"

class Camera : public GameObject {
public:
    Camera();
    void ProcessInput(GLFWwindow *window, float deltaTime);
private:
    glm::vec2 mouseLastPos;
    float pitch = 0; // x rotation (up or down)
    float heading = 0; // y rotation or yaw
    // We don't use bank!!!
};
