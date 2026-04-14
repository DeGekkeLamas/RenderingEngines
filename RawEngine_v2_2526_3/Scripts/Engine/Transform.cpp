#include "Transform.hpp"

#include "VectorMath.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "imgui_impl_opengl3_loader.h"

Transform::~Transform() {

}

glm::mat4 Transform::getModelMatrix() const {
    if (parent == nullptr || parent == this) return modelMatrix;
    else return parent->getModelMatrix() * modelMatrix;
}

void Transform::AddChild(Transform *child) {
    children.push_back(child);
    child->parent = this;
}

glm::vec3 Transform::right() const {
    return column(modelMatrix, 0);
}

glm::vec3 Transform::up() const {
    return column(modelMatrix, 1);
}


glm::vec3 Transform::forward() const {
    return column(modelMatrix, 2);
}

glm::vec3 Transform::position() const {
    const glm::vec3 translation = column(modelMatrix, 3);
    return translation;
}

void Transform::TranslateObjectSpace(const glm::vec3 amount) {
    modelMatrix = translate(modelMatrix, amount);
}

void Transform::TranslateWorldSpace(const glm::vec3 amount) {
    modelMatrix[3] += glm::vec4(amount, 0);
}
void Transform::SetPosition(const glm::vec3 position) {
    modelMatrix[3] = glm::vec4(position, modelMatrix[3][3]);
}

void Transform::SetRotationRadians(const glm::vec3 radians) {
    const glm::vec4 currentTranslation = column(modelMatrix, 3); // ?

    glm::mat4 rot(1); // identity
    // apply the heading / Y:
    rot = glm::rotate(rot,radians.y, glm::vec3(0,1,0));
    // apply the pitch / X:
    rot = glm::rotate(rot,radians.x, glm::vec3(1,0,0));
    // apply the bank / Z:
    rot = glm::rotate(rot,radians.z, glm::vec3(0,0,1));

    rot[3] = currentTranslation;
    modelMatrix = rot;
}

void Transform::SetRotationEuler(const glm::vec3 euler) {
    SetRotationRadians(euler * 3.14159f / 180.0f);
}

void Transform::Rotate(const glm::vec3 amount) {
    // Z
    RotateOneDir(amount.z, glm::vec3(0,0, 1));
    // X
    RotateOneDir(amount.x, glm::vec3(1,0, 0));
    // Y
    RotateOneDir(amount.y, glm::vec3(0,1, 0));
}
void Transform::RotateWorld(const glm::vec3 amount) {
    // Z
    RotateOneDirWorld(amount.z, forward());
    // X
    RotateOneDirWorld(amount.x, right());
    // Y
    RotateOneDirWorld(amount.y, up());
}

void Transform::LookAt(glm::vec3 forward, glm::vec3 up) {
    forward = glm::normalize(forward);
    glm::vec3 right = glm::normalize(cross(forward, up));
    up = cross(right, forward);
    // Set directions
    modelMatrix[0] = glm::vec4(right * scale.x, modelMatrix[0][3]);
    modelMatrix[1] = glm::vec4(up * scale.y, modelMatrix[1][3]);
    modelMatrix[2] = glm::vec4(forward * scale.z, modelMatrix[2][3]);
}


void Transform::RotateOneDir(const float amount, const glm::vec3 axis) {
    modelMatrix = glm::rotate(modelMatrix, amount, axis);
}

void Transform::RotateOneDirWorld(const float amount, const glm::vec3 axis) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), amount, axis);
    modelMatrix = rotation * modelMatrix; // pre-multiply
}


void Transform::Scale(const glm::vec3 amount) {
    modelMatrix = glm::scale(modelMatrix, amount);
    scale = amount;
}