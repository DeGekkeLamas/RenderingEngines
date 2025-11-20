#pragma once

#include "iostream"
#include "Transform.hpp"
#include "../core/model.h"
#include "../core/texture.h"

class GameObject {
    public:
    GameObject(const std::string &name);
    GameObject(const std::string &name, glm::vec3 position, Transform* parent);
    std::string name;
    Transform transform;

    virtual void Start();
    virtual void Update();
};
