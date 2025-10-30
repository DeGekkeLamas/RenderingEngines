#include "Transform.hpp"
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
    // return glm::normalize(position - rotationTarget);
    return column(modelMatrix, 2);
}

glm::vec3 Transform::position() const {
    const glm::vec3 translation = column(modelMatrix, 3);
    VectorMath::PrintVec3(translation);
    return translation;
}

void Transform::Translate(const glm::vec3 amount) {
    modelMatrix = translate(modelMatrix, amount);
}