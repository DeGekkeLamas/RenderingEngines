#include "BoidObject.hpp"

#include "imgui.h"
#include "Scripts/Engine/VectorMath.hpp"
#include <glm/gtc/type_ptr.hpp>

std::vector<BoidObject*> BoidObject::boids;
KDTree<BoidObject*> BoidObject::boidsTree;
float BoidObject::speed;
float BoidObject::perceivedCenterStrength;
float BoidObject::keepDistanceStrength;
float BoidObject::averageVelocityStrength;
float BoidObject::moveToCenterStrength;
float BoidObject::repellingDistance;

void BoidObject::Awake() {
    boids.push_back(this);
}

void BoidObject::Update(const float deltaTime, bool useSectioning) {
    glm::vec3 perceivedCenter = glm::vec3();
    glm::vec3 keepDistance = glm::vec3();
    glm::vec3 averageVelocity = glm::vec3();
    glm::vec3 moveToCenter;

    int boidNum = boids.size();
    BoidObject** boidsUsed = !useSectioning ? boids.data() : boidsTree.FindNeighbours(this, boidNum);
        // std::cout << boidNum << std::endl;
    for (int i = 0; i < boidNum; i++) {
        const BoidObject* otherBoid = boidsUsed[i];
        if (otherBoid == this) continue;

        // Center of mass
        perceivedCenter += otherBoid->transform.position();
        // Distance from other boids
        if (glm::length(transform.position() - otherBoid->transform.position()) < repellingDistance) {
            keepDistance -= otherBoid->transform.position() - transform.position();
        }
        // Match velocity
        averageVelocity += otherBoid->velocity;
    }
    perceivedCenter /= glm::max(boidNum-1, 1);
    perceivedCenter -= this->transform.position();
    averageVelocity /= glm::max(boidNum-1, 1);
    moveToCenter = -transform.position(); // Steer boid towards origin of scene

    // Set velocities
    velocity += deltaTime * perceivedCenterStrength * perceivedCenter;
    velocity += deltaTime * keepDistanceStrength * keepDistance;
    velocity += deltaTime * averageVelocityStrength * (averageVelocity - velocity);
    velocity += deltaTime * moveToCenterStrength * moveToCenter;
    // Update position
    transform.TranslateWorldSpace(deltaTime * speed * velocity);
    transform.LookAt(velocity, VectorMath::up);
}

void BoidObject::RenderToIMGUI() {
    RenderableObject::RenderToIMGUI();
    // pos
    ImGui::DragFloat3("Velocity", glm::value_ptr(velocity));
}

SimpleBoidData BoidObject::ToSimpleData() const {
    return SimpleBoidData(make_vec4(transform.position()), make_vec4(velocity));
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

void BoidObject::ResetAllBoids() {
    for (int i = 0; i < boids.size(); i++) {
        boids[i]->transform.SetPosition(glm::vec3(rand()%100,rand()%100,rand()%100));
        boids[i]->velocity = glm::normalize(boids[i]->transform.position()) * 1.0f;
    }
}







