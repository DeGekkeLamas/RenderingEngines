#pragma once
#include "Scripts/Engine/RenderableObject.hpp"

class BoidObject : public RenderableObject {
public:
        BoidObject(const std::string &name, glm::vec3 position, Transform* parent,
        std::shared_ptr<core::Model> model, std::shared_ptr<Material> material) : RenderableObject(name, position, parent, model, material) {};
        glm::vec3 velocity = glm::vec3(1, 1, 1);
        static std::vector<BoidObject*> boids;
        void Awake();
        void Update(float deltaTime);
        void RenderToIMGUI() override;
};


