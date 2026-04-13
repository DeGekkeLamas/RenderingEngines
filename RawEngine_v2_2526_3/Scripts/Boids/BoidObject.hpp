#pragma once
#include "SimpleBoidData.hpp"
#include "Scripts/Engine/RenderableObject.hpp"

class BoidObject : public RenderableObject {
public:
        BoidObject(const std::string &name, glm::vec3 position, Transform* parent,
        std::shared_ptr<core::Model> model, std::shared_ptr<Material> material) : RenderableObject(name, position, parent, model, material) {};
        glm::vec3 velocity;
        void Awake();
        void Update(float deltaTime);
        void RenderToIMGUI() override;
        SimpleBoidData ToSimpleData() const;
        void FromSimpleData(const SimpleBoidData* data);

        static std::vector<BoidObject*> boids;
        static SimpleBoidData* ToSimpleArray();
        static void FromSimpleArray(const SimpleBoidData* data);
};


