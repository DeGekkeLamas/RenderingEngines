#pragma once
#include "Camera.hpp"
#include "iostream"
#include "GameObject.hpp"
#include "Material.hpp"
#include "PointLight.hpp"

class RenderableObject : public GameObject {
public:
    RenderableObject(const std::string &name, glm::vec3 position, Transform* parent, core::Model* model, Material* material);
    core::Model* model;
    Material* material;
    void Render(const glm::mat4 &view, const glm::mat4 &projection, GLint textureModelUniform,
        const PointLight &light, const Camera &camera);
};
