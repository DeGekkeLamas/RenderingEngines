#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Simple class containing needed data of a BoidObject for passing it to a compute shader
struct SimpleBoidData {
    SimpleBoidData(glm::vec4 position, glm::vec4 velocity);
    SimpleBoidData();
    glm::vec4 position;
    glm::vec4 velocity;
};
