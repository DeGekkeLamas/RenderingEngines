#pragma once
#include "Scripts/Engine/RenderableObject.hpp"

class BoidObject : public RenderableObject {
public:
        glm::vec3 velocity;
        std::vector<BoidObject*> boids;
        void Awake();
        void Update(float deltaTime);
};


