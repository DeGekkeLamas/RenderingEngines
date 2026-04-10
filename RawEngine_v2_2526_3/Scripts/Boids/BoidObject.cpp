#include "BoidObject.hpp"

#include "imgui.h"
#include "Scripts/Engine/VectorMath.hpp"

std::vector<BoidObject*> BoidObject::boids;

void BoidObject::Awake() {
    boids.push_back(this);
}

void BoidObject::Update(const float deltaTime) {
    glm::vec3 perceivedCenter = glm::vec3();
    glm::vec3 keepDistance = glm::vec3();
    glm::vec3 averageVelocity = glm::vec3();
    glm::vec3 moveToCenter = glm::vec3();
    for (int i = 0; i < boids.size(); i++) {
        BoidObject* currentBoid = boids[i];
        if (currentBoid == this) continue;

        // Center of mass
        perceivedCenter += currentBoid->transform.position();
        // Distance from other boids
        if (glm::length(transform.position() - currentBoid->transform.position()) < 5) {
            keepDistance -= currentBoid->transform.position() - transform.position();
        }
        // Match velocity
        averageVelocity += currentBoid->velocity;
    }
    perceivedCenter /= boids.size()-1;
    perceivedCenter -= this->transform.position();
    averageVelocity /= boids.size()-1;
    moveToCenter = -transform.position(); // Steer boid towards origin of scene

    velocity += perceivedCenter * deltaTime;
    velocity += keepDistance * deltaTime;
    velocity += (averageVelocity - velocity) * deltaTime;
    velocity += moveToCenter * deltaTime;
    transform.TranslateWorldSpace(velocity * deltaTime);
    transform.LookAt(velocity, VectorMath::up);
}

void BoidObject::RenderToIMGUI() {
    RenderableObject::RenderToIMGUI();
    // pos
    ImGui::DragFloat3("Velocity", glm::value_ptr(velocity));
}




