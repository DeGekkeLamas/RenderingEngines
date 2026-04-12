#pragma once
#include <glm/vec3.hpp>

// Simple class containing needed data of a BoidObject for passing it to a compute shader
struct SimpleBoidData {
    SimpleBoidData(glm::vec3 position, glm::vec3 velocity);
    SimpleBoidData();
    glm::vec3 position;
    glm::vec3 velocity;
};
