#include <valarray>
#include <glm/vec3.hpp>
#include "VectorMath.hpp"

/// <summary>
/// Rotation over Y-axis
/// </summary>
glm::vec3 VectorMath::RotateVectorXZ(glm::vec3 start, const float rotation)
{
    // rotation = DegreesToRadians(rotation);
    return glm::vec3(
            start.x * std::cos(rotation) - start.z * std::sin(rotation)
            , start.y
            , start.x * std::sin(rotation) + start.z * std::cos(rotation)
        );
}
/// <summary>
/// Rotation over X-axis
/// </summary>
glm::vec3 VectorMath::RotateVectorYZ(glm::vec3 start, const float rotation)
{
    // rotation = DegreesToRadians(rotation);
    return glm::vec3(
            start.x,
            start.y * std::cos(rotation) - start.z * std::sin(rotation)
            , start.y * std::sin(rotation) + start.z * std::cos(rotation)
        );
}
/// <summary>
/// Rotation over Z-axis
/// </summary>
glm::vec3 VectorMath::RotateVectorXY(glm::vec3 start, const float rotation)
{
    // rotation = DegreesToRadians(rotation);
    return glm::vec3(
            start.x * std::cos(rotation) - start.y * std::sin(rotation)
            , start.x * std::sin(rotation) + start.y * std::cos(rotation)
            , start.z
        );
}
/// <summary>
/// Rotate over all axes at once
/// </summary>
glm::vec3 VectorMath::RotateVector3(glm::vec3 originalVector, const glm::vec3 rotation)
{
    // ZXY
    originalVector = RotateVectorXZ(originalVector, rotation.z); // Z
    originalVector = RotateVectorYZ(originalVector, rotation.x); // X
    originalVector = RotateVectorXZ(originalVector, rotation.y); // Y
    return originalVector;
}

void VectorMath::PrintVec3(glm::vec3 const& vec) {
    printf("Vec = (%f, %f, %f)\n", vec.x, vec.y, vec.z);
}