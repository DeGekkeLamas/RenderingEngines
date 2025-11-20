#pragma once
#include "iostream"
#include "GameObject.hpp"
#include "Material.hpp"

class RenderableObject : public GameObject {
public:
    RenderableObject(const std::string &name, glm::vec3 position, Transform* parent, core::Model* model, Material* material);
    core::Model* model;
    Material* material;
    unsigned int shaderProgram;
};
