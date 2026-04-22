#include "GameObject.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"

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

void GameObject::RenderToIMGUI() {
    ImGui::Text("%s", this->name.c_str());
    // pos
    glm::vec3 tempPos = this->transform.position();
    ImGui::DragFloat3("Position", glm::value_ptr(tempPos));
    this->transform.SetPosition(tempPos);
}


void GameObject::Update() {

}

void GameObject::Start() {

}




