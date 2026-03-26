#pragma once
#include "Scripts/Engine/RenderableObject.hpp"

class BoidObject : public RenderableObject {
public:
        glm::vec3 velocity;
        std::vector<BoidObject*> boids;
        void Awake();
        void Update(float deltaTime);
private:
        glm::vec3 FlyToCenterOfMass(BoidObject* compare);
        glm::vec3 KeepDistance(BoidObject* compare);
        glm::vec3 MatchVelocity(BoidObject* compare);
};


