#pragma once

#include "Transform.hpp"

class GameObject {
    public:
    GameObject(std::string name);
    GameObject(std::string name, Transform parent);
    GameObject(std::string name, glm::vec3 position, Transform parent);
    std::string name;
    Transform transform;
    //T GetComponent<T>();

    virtual void Start();
    virtual void Update();
};
