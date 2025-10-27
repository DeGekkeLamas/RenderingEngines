#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include <glm/vec3.hpp>
#include "Transform.hpp"

class Camera {
public:
    Transform transform;
    glm::vec3 cameraTarget;
    Camera();
    void SetCameraValues();
    void ProcessInput(GLFWwindow *window);
    void RotateAroundCamera(glm::vec3 rotation);
private:
    // ImVec2 mouseLastPos;
};
