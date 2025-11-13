
#include "Scene.hpp"

Scene::Scene(const std::vector<GameObject*> &sceneObjects) {
    this->sceneObjects = sceneObjects;
}

void Scene::LoadScene(const Scene &toLoad, std::vector<GameObject*>& target) {
    target.clear();
    target = toLoad.sceneObjects;
}
