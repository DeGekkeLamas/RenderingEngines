
#include "Scene.hpp"

Scene::Scene(const std::vector<GameObject> sceneObjects) {
    this->sceneObjects = sceneObjects;
}

std::vector<GameObject> Scene::LoadScene(const Scene &toLoad) {
    return toLoad.sceneObjects;
}
