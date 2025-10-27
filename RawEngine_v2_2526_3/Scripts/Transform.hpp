#pragma once
#include <vector>
#include <glm/glm.hpp>

class Transform {
    public:
        Transform();
        ~Transform();
        glm::mat4 modelMatrix;
        glm::vec3 position = glm::vec3(0,0,0);
        glm::vec3 rotation = glm::vec3(0,0,0);
        glm::vec3 scale = glm::vec3(1,1,1);
        Transform* parent;
        std::vector<Transform*> children;
        // Directions
        glm::vec3 right();
        glm::vec3 up();
        glm::vec3 forward();
    private:
        glm::vec3 rotationTarget;
};




