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
        BoidObject* otherBoid = boids[i];
        if (otherBoid == this) continue;

        // Center of mass
        perceivedCenter += otherBoid->transform.position();
        // Distance from other boids
        if (glm::length(transform.position() - otherBoid->transform.position()) < 5) {
            keepDistance -= otherBoid->transform.position() - transform.position();
        }
        // Match velocity
        averageVelocity += otherBoid->velocity;
    }
    perceivedCenter /= boids.size()-1;
    perceivedCenter -= this->transform.position();
    averageVelocity /= boids.size()-1;
    moveToCenter = -transform.position(); // Steer boid towards origin of scene

    // Set velocities
    velocity += perceivedCenter * deltaTime;
    velocity += keepDistance * deltaTime;
    velocity += (averageVelocity - velocity) * deltaTime;
    velocity += moveToCenter * deltaTime;
    // Update position
    transform.TranslateWorldSpace(velocity * deltaTime);
    transform.LookAt(velocity, VectorMath::up);
}

void BoidObject::RenderToIMGUI() {
    RenderableObject::RenderToIMGUI();
    // pos
    ImGui::DragFloat3("Velocity", glm::value_ptr(velocity));
}

SimpleBoidData BoidObject::ToSimpleData() const {
    return SimpleBoidData(transform.position(), velocity);
}

void BoidObject::FromSimpleData(const SimpleBoidData* data) {
    // std::cout << "Changed velocity from " << velocity.x << " to " << data->velocity.x << std::endl;
    transform.SetPosition(data->position);
    velocity = data->velocity;
    transform.LookAt(velocity, VectorMath::up);
}


SimpleBoidData* BoidObject::ToSimpleArray() {
    SimpleBoidData* boidsData = new SimpleBoidData[boids.size()];
    for (int i = 0; i < boids.size(); i++) {
        boidsData[i] = boids[i]->ToSimpleData();
    }
    return  boidsData;
}

void BoidObject::FromSimpleArray(const SimpleBoidData* data) {
    for (int i = 0; i < boids.size(); i++) {
        boids[i]->FromSimpleData(&data[i]);
    }
}






