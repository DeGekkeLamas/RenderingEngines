#pragma once

#include "iostream"
#include "Transform.hpp"
#include "../core/model.h"
#include "../core/texture.h"

class GameObject {
    public:
    virtual ~GameObject() = default;

    GameObject(const std::string &name);
    GameObject(const std::string &name, glm::vec3 position, Transform* parent);
    std::string name;
    Transform transform;
    void RenderToIMGUI();

    virtual void Start();
    virtual void Update();
};
