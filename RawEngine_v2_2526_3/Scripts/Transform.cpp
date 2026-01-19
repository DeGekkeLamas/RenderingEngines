#include "Transform.hpp"

#include "VectorMath.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

Transform::~Transform() {

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
    // Apply to children
    for (int i = 0; i < children.size(); i++) {
        children[i]->TranslateObjectSpace(amount);
    }
}

void Transform::TranslateWorldSpace(const glm::vec3 amount) {
    modelMatrix[3] += glm::vec4(amount, 0);
    // Apply to children
    for (int i = 0; i < children.size(); i++) {
        children[i]->TranslateWorldSpace(amount);
    }
}
void Transform::SetPosition(const glm::vec3 position) {
    modelMatrix[3] = glm::vec4(position, 1);
    // Apply to children
    for (int i = 0; i < children.size(); i++) {
        children[i]->SetPosition(position);
    }
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

void Transform::RotateOneDir(const float amount, const glm::vec3 axis) {
    modelMatrix = glm::rotate(modelMatrix, amount, axis);
}

void Transform::RotateOneDirWorld(const float amount, const glm::vec3 axis) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), amount, axis);
    modelMatrix = rotation * modelMatrix; // pre-multiply
}


void Transform::Scale(const glm::vec3 amount) {
    modelMatrix = glm::scale(modelMatrix, amount);
}