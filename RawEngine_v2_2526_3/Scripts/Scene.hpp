#pragma once

#include <vector>

#include "GameObject.hpp"
#include "iostream"

class Scene {
    public:
    Scene(const std::vector<GameObject> sceneObjects);
    std::vector<GameObject> sceneObjects;
    static std::vector<GameObject> LoadScene(const Scene &toLoad);
};
