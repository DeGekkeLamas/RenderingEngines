#include "BoidObject.hpp"

void BoidObject::Awake() {
    boids.push_back(this);
}


void BoidObject::Update(float deltaTime) {
    glm::vec3 perceivedCenter = glm::vec3();
    for (int i = 0; i < boids.size(); i++) {
        BoidObject* currentBoid = boids[i];
        if (currentBoid == this) continue;

        // Center of mass
        perceivedCenter += currentBoid->transform.position();
    }
    perceivedCenter /= boids.size()-1;
    perceivedCenter -= this->transform.position();

    velocity += perceivedCenter;
    transform.TranslateWorldSpace(velocity);
}

glm::vec3 BoidObject::FlyToCenterOfMass(BoidObject* compare) {
    glm::vec3 perceivedCenter;
}

glm::vec3 BoidObject::KeepDistance(BoidObject* compare) {

}

glm::vec3 BoidObject::MatchVelocity(BoidObject* compare) {

}


