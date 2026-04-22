#include "PointLight.hpp"

PointLight::PointLight(const std::string &name, glm::vec3 position, Transform* parent, glm::vec4 color, float intensity)
    : GameObject(name, position, parent) {
    this->color = color;
    this->intensity = intensity;
}