#include "iostream"
#include "GameObject.hpp"

class RenderableObject : public GameObject {
public:
    RenderableObject(const std::string &name, glm::vec3 position, Transform* parent, core::Model* model, core::Texture* texture);
    core::Model* model;
    core::Texture* texture;
};
