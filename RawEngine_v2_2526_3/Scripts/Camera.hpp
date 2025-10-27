#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "VectorMath.hpp"

class Camera {
public:
    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection;
    glm::vec3 cameraUp;
    Camera();
    void SetCameraValues();
    void ProcessInput(GLFWwindow *window);
    void RotateAroundCamera(glm::vec3 rotation);
private:
    glm::vec3 up;
    glm::vec3 cameraRight;
    ImVec2 mouseLastPos;
};

Camera::Camera() {
    cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    SetCameraValues();
    printf("Created a camera\n");
}

void Camera::SetCameraValues() {
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
}

void Camera::RotateAroundCamera(glm::vec3 rotation) {
    cameraTarget = VectorMath::RotateVector3(cameraTarget - cameraPos, rotation) + cameraPos;
}

void Camera::ProcessInput(GLFWwindow *window) {
    const float moveSpeed = 0.01f;
    const float rotateSpeed = 0.001f;
    // Rotation
    // Down
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        const glm::vec3 increment = glm::vec3(-rotateSpeed, 0.0f, 0.0f);
        RotateAroundCamera(increment);
    }
    // Up
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        const glm::vec3 increment = glm::vec3(rotateSpeed, 0.0f, 0.0f);
        RotateAroundCamera(increment);
    }
    // Left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        const glm::vec3 increment = glm::vec3(0.0f, -rotateSpeed, 0.0f);
        RotateAroundCamera(increment);
    }
    // Right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        const glm::vec3 increment = glm::vec3(0.0f, rotateSpeed, 0.0f);
        RotateAroundCamera(increment);
    }

    // Movement
    // X
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        const glm::vec3 increment = -moveSpeed * cameraRight;
        cameraPos += increment;
        cameraTarget += increment;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        const glm::vec3 increment = moveSpeed * cameraRight;
        cameraPos += increment;
        cameraTarget += increment;
    }
    // Y
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        const glm::vec3 increment = moveSpeed * cameraUp;
        cameraPos += increment;
        cameraTarget += increment;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        const glm::vec3 increment = -moveSpeed * cameraUp;
        cameraPos += increment;
        cameraTarget += increment;
    }
    // Z
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        const glm::vec3 increment = -moveSpeed * cameraDirection;
        cameraPos += increment;
        cameraTarget += increment;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        const glm::vec3 increment = moveSpeed * cameraDirection;
        cameraPos += increment;
        cameraTarget += increment;
    }
}