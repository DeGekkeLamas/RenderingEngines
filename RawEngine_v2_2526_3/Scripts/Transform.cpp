#include "Transform.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>

#include "VectorMath.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

Transform::~Transform() {

}

glm::vec3 Transform::right() const {
    // return glm::normalize(glm::cross(VectorMath::up, forward() ) );
    // VectorMath::PrintVec3(column(modelMatrix, 0));
    return column(modelMatrix, 0);
}

glm::vec3 Transform::up() const {
    // return glm::cross(forward(), right());
    return column(modelMatrix, 1);
}


glm::vec3 Transform::forward() const {
    VectorMath::PrintVec3(column(modelMatrix, 2));
    return column(modelMatrix, 2);
}

glm::vec3 Transform::position() const {
    const glm::vec3 translation = column(modelMatrix, 3);
    // VectorMath::PrintVec3(translation);
    return translation;
}

void Transform::Translate(const glm::vec3 amount) {
    modelMatrix = translate(modelMatrix, amount);
}

void Transform::Rotate(const glm::vec3 amount) {
    // Z
    RotateOneDir(amount.z, glm::vec3(0,0, 1));
    // X
    RotateOneDir(amount.x, glm::vec3(1,0, 0));
    // Y
    RotateOneDir(amount.y, glm::vec3(0,1, 0));
}

void Transform::RotateOneDir(const float amount, const glm::vec3 axis) {
    modelMatrix = glm::rotate(modelMatrix, amount, axis);
}