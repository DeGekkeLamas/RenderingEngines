#include "GameObject.hpp"

GameObject::GameObject(const std::string &name) {
    this->name = name;
}
GameObject::GameObject(const std::string &name, glm::vec3 position, Transform* parent) {
    this->name = name;
    this->transform.parent = parent;
    this->transform.SetPosition(position);
}
GameObject::GameObject(const std::string &name, glm::vec3 position, Transform* parent,
    core::Model* model, core::Texture* texture) {
    this->name = name;
    this->transform.parent = parent;
    this->transform.SetPosition(position);
    this->model = model;
    this->texture = texture;
}


void GameObject::Update() {

}

void GameObject::Start() {

}




