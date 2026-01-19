#pragma once
#include <vector>
#include <glm/glm.hpp>

class Transform {
    public:
        Transform() : modelMatrix(1) {};
        ~Transform();
        glm::mat4 modelMatrix;
        glm::vec3 scale = glm::vec3(1,1,1);
        Transform* parent;
        std::vector<Transform*> children;
        void AddChild(Transform* child);
        // void RemoveChild(Transform* child);
        // Directions
        glm::vec3 right() const;
        glm::vec3 up() const;
        glm::vec3 forward() const;

        glm::vec3 position() const;

        void SetPosition(glm::vec3 position);
        void TranslateObjectSpace(const glm::vec3 amount);
        void TranslateWorldSpace(const glm::vec3 amount);
        void Rotate(const glm::vec3 amount);
        void RotateLocal(const glm::vec3 amount);
        void Scale(const glm::vec3 amount);
    private:
        void RotateOneDir(const float amount, const glm::vec3 axis);
};




