#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "GameObject.hpp"

class Camera : public GameObject {
public:
    Camera();
    void ProcessInput(GLFWwindow *window);
    void Update() override;
private:
    // ImVec2 mouseLastPos;
};
