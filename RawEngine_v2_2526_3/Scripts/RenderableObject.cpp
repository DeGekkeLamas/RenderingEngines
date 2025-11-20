#include "RenderableObject.hpp"


RenderableObject::RenderableObject(const std::string &name, glm::vec3 position, Transform* parent,
    core::Model* model, Material* material) : GameObject(name, position, parent) {
    this->model = model;
    this->material = material;
}
