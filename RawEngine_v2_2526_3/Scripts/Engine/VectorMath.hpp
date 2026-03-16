#pragma once
#include <glm/vec3.hpp>

class VectorMath {
    public:
        static glm::vec3 RotateVectorXZ(glm::vec3 start, const float rotation);
        static glm::vec3 RotateVectorYZ(glm::vec3 start, const float rotation);
        static glm::vec3 RotateVectorXY(glm::vec3 start, const float rotation);
        static glm::vec3 RotateVector3(glm::vec3 originalVector, glm::vec3 rotation);
        static void PrintVec3(glm::vec3 const& vec);
        // Cardinal directions
        static constexpr glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
        static constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        static constexpr glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
};