#pragma once

#include "iostream"
#include "Transform.hpp"
#include "../core/model.h"
#include "../core/texture.h"

class GameObject {
    public:
    GameObject(const std::string &name);
    GameObject(const std::string &name, glm::vec3 position, Transform* parent);
    GameObject(const std::string &name, glm::vec3 position, Transform* parent, core::Model* model, core::Texture* texture);
    std::string name;
    Transform transform;

    core::Model* model;
    core::Texture* texture;

    virtual void Start();
    virtual void Update();
};
