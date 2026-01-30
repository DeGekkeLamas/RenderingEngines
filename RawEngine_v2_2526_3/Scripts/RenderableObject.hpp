#pragma once
#include "Camera.hpp"
#include "iostream"
#include "GameObject.hpp"
#include "Material.hpp"
#include "PointLight.hpp"

class RenderableObject : public GameObject {
public:
    RenderableObject(const std::string &name, glm::vec3 position, Transform* parent,
        std::shared_ptr<core::Model>, std::shared_ptr<Material> material);
    std::shared_ptr<core::Model> model;
    std::shared_ptr<Material> material;
    void Render(const glm::mat4 &view, const glm::mat4 &projection, GLint textureModelUniform,
        const PointLight &light, const Camera &camera) const;
    void Render(const glm::mat4 &view, const glm::mat4 &projection, GLint textureModelUniform,
        const PointLight &light, const Camera &camera, const GLuint texture) const;
    void Render(const GLuint texture) const;
    // Create into scene
    RenderableObject Clone() const;
    static RenderableObject Create(const std::string &name, const glm::vec3 position, const glm::vec3 scale, Transform* parent,
        const std::string &modelPath, std::shared_ptr<Material> material);
    static RenderableObject Create(const std::string &name, const glm::vec3 position, const glm::vec3 scale, Transform* parent,
        const std::string &modelPath, const std::string &texturePath, const GLuint modelVertexShader, const GLuint textureShader);
};
