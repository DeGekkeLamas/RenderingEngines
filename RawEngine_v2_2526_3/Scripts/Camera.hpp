#pragma once

#include "GameObject.hpp"

class Camera : public GameObject {
public:
    Camera();
    void ProcessInput(GLFWwindow *window, float deltaTime);
    void Update() override;
private:
    // ImVec2 mouseLastPos;
};
