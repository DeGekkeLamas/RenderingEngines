#include "GameObject.hpp"

GameObject::GameObject(const std::string &name) {
    this->name = name;
}
GameObject::GameObject(const std::string &name, glm::vec3 position, Transform* parent) {
    this->name = name;
    if (parent != nullptr) {
        parent->AddChild(&this->transform);
    }
    this->transform.SetPosition(position);
}

void GameObject::Update() {

}

void GameObject::Start() {

}




