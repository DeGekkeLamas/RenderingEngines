#include <iostream>
#include "VectorMath.hpp"
#include "Camera.hpp"
#include <glm/ext/quaternion_geometric.hpp>

Camera::Camera() {
    transform.Translate(glm::vec3(0.0f, 0.0f, 10.0f));
    printf("Created a camera\n");
}

void Camera::RotateAroundCamera(glm::vec3 rotation) {
    transform.Rotate(rotation);
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
        const glm::vec3 increment = -moveSpeed * transform.right();
        transform.Translate(increment);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        const glm::vec3 increment = moveSpeed * transform.right();
        transform.Translate(increment);
    }
    // Y
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        const glm::vec3 increment = moveSpeed * transform.up();
        transform.Translate(increment);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        const glm::vec3 increment = -moveSpeed * transform.up();
        transform.Translate(increment);
    }
    // Z
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        const glm::vec3 increment = -moveSpeed * transform.forward();
        transform.Translate(increment);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        const glm::vec3 increment = moveSpeed * transform.forward();
        transform.Translate(increment);
    }
}