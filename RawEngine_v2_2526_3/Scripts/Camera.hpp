#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include <glm/vec3.hpp>
#include "Transform.hpp"

class Camera {
public:
    Transform transform;
    Camera();
    void ProcessInput(GLFWwindow *window);
private:
    // ImVec2 mouseLastPos;
};
