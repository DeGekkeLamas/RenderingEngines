#pragma once
#include "GameObject.hpp"

class PointLight : public GameObject{
    public:
    PointLight(const std::string &name, glm::vec3 position, Transform* parent, glm::vec4 color, float intensity);
    glm::vec4 color;
    float intensity;
};