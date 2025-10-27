#include "Transform.hpp"
#include "VectorMath.hpp"

Transform::Transform() {

}

Transform::~Transform() {

}

glm::vec3 Transform::right() {
    return glm::normalize(glm::cross(VectorMath::up, forward() ) );
}

glm::vec3 Transform::up() {
    return glm::cross(forward(), right());
}


glm::vec3 Transform::forward() {
    return glm::normalize(position - rotationTarget);
}