#pragma once

#include <vector>
#include "GameObject.hpp"
#include "iostream"

class Scene {
    public:
    Scene(const std::vector<GameObject*> &sceneObjects);
    std::vector<GameObject*> sceneObjects;
    static void LoadScene(const Scene &toLoad, std::vector<GameObject*>& target);
};
