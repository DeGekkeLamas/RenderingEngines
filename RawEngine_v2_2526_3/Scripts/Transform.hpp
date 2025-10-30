#pragma once
#include <vector>
#include <glm/glm.hpp>

class Transform {
    public:
        Transform() : modelMatrix(1) {};
        ~Transform();
        glm::mat4 modelMatrix;
        // glm::vec3 position = glm::vec3(0,0,0);
        glm::vec3 rotation = glm::vec3(0,0,0);
        glm::vec3 scale = glm::vec3(1,1,1);
        Transform* parent;
        std::vector<Transform*> children;
        // Directions
        glm::vec3 right() const;
        glm::vec3 up() const;
        glm::vec3 forward() const;

        glm::vec3 position() const;
        void Translate(glm::vec3 amount);
    private:
        glm::vec3 rotationTarget;
};




