#include <iostream>
#include "VectorMath.hpp"
#include "Camera.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>

Camera::Camera() : GameObject("Camera", glm::vec3(0.0f, 0.0f, 10.0f), nullptr) {
    printf("Created a camera\n");
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime) {
    constexpr float moveSpeed = 10.0f;
    constexpr float rotateSpeed = 300.0f;

    constexpr glm::vec3 right(1.0f, 0.0f, 0.0f);
    constexpr glm::vec3 up(0.0f, 1.0f, 0.0f);
    constexpr glm::vec3 forward(0.0f, 0.0f, 1.0f);

    glm::vec3 incrementR;
    glm::vec3 incrementT = glm::vec3(0,0,0);

    // Rotation
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glm::vec2 mousePos(xpos, ypos);
    incrementR = glm::vec3(mousePos - mouseLastPos,0) * deltaTime * rotateSpeed;
    mouseLastPos = mousePos;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        pitch += incrementR.y;
        heading += -incrementR.x;
        transform.SetRotationEuler(glm::vec3(pitch,heading,0));
        // std::cout << "pitch: " << pitch << ", heading:" << heading << "\n";
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
