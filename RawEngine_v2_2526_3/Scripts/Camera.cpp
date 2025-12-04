#include <iostream>
#include "VectorMath.hpp"
#include "Camera.hpp"

Camera::Camera() : GameObject("Camera", glm::vec3(0.0f, 0.0f, 10.0f), NULL) {
    printf("Created a camera\n");
}
void Camera::Update() {
    // ProcessInput(window);
}

void Camera::ProcessInput(GLFWwindow *window, float deltaTime) {
    constexpr float moveSpeed = 10.0f;
    constexpr float rotateSpeed = 1.0f;

    constexpr glm::vec3 right(1.0f, 0.0f, 0.0f);
    constexpr glm::vec3 up(0.0f, 1.0f, 0.0f);
    constexpr glm::vec3 forward(0.0f, 0.0f, 1.0f);

    glm::vec3 incrementR = glm::vec3(0,0,0);
    glm::vec3 incrementT = glm::vec3(0,0,0);

    // Rotation
    // Down
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        incrementR += rotateSpeed * right;
    }
    // Up
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        incrementR += -rotateSpeed * right;
    }
    // Left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        incrementR += rotateSpeed * up;
    }
    // Right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        incrementR += -rotateSpeed * up;
    }
    // Apply
    if (incrementR != glm::vec3(0, 0, 0)) {
        transform.Rotate(incrementR * deltaTime);
    }

    // Movement
    // X
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        incrementT += moveSpeed * right;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        incrementT += -moveSpeed * right;
    }
    // Y
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        incrementT += moveSpeed * up;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        incrementT += -moveSpeed * up;
    }
    // Z
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        incrementT += moveSpeed * forward;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        incrementT += -moveSpeed * forward;
    }
    // Apply
    if (incrementT != glm::vec3(0, 0, 0)) {
        transform.TranslateObjectSpace(incrementT * deltaTime);
    }
}
