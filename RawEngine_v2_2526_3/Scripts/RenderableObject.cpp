#include "RenderableObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "assimpLoader.h"
#include "Camera.hpp"
#include "PointLight.hpp"


RenderableObject::RenderableObject(const std::string &name, const glm::vec3 position, Transform* parent,
    std::shared_ptr<core::Model> model, std::shared_ptr<Material> material) : GameObject(name, position, parent)
{
    this->model = model;
    this->material = material;
}


void RenderableObject::Render(const glm::mat4 &view, const glm::mat4 &projection,
    const GLint textureModelUniform, const PointLight &light, const Camera &camera) const
{
    GLuint texture = material->texture != nullptr ? material->texture->getId() : NULL;
    Render(view, projection, textureModelUniform, light, camera, texture);
}

void RenderableObject::Render(const glm::mat4 &view, const glm::mat4 &projection,
    const GLint textureModelUniform, const PointLight &light, const Camera &camera, const GLuint texture) const
{
    glUseProgram(*material->shaderProgram);
    glUniformMatrix4fv(textureModelUniform, 1, GL_FALSE, glm::value_ptr(projection *
        view * transform.getModelMatrix()));
    glActiveTexture(GL_TEXTURE0);
    // Uniforms
    material->SetUniform("lightColor", light.color);
    material->SetUniform("lightPos", light.transform.position());
    material->SetUniform("camPos", camera.transform.position());
    material->SetUniform("lightStrength", light.intensity);
    material->SetUniform("modelMatrix", transform.getModelMatrix());

    glBindTexture(GL_TEXTURE_2D, texture);

    model->render();
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void RenderableObject::Render(const GLuint texture) const {
    glUseProgram(*material->shaderProgram);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);

    model->render();
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}


RenderableObject RenderableObject::Clone() const {
    return RenderableObject(*this);
}


RenderableObject RenderableObject::Create(const std::string &name, const glm::vec3 position, const glm::vec3 scale, Transform *parent,
    const std::string &modelPath, std::shared_ptr<Material> material)
{
    std::shared_ptr<core::Model> model = std::shared_ptr<core::Model>(new core::Model( core::AssimpLoader::loadModel(modelPath) ) );
    RenderableObject obj(name, position, parent, model, material);
    obj.transform.Scale(scale);
    return obj;
}

RenderableObject RenderableObject::Create(const std::string &name, const glm::vec3 position, const glm::vec3 scale, Transform *parent,
    const std::string &modelPath, const std::string &texturePath, const GLuint modelVertexShader, const GLuint textureShader)
{
    std::shared_ptr<core::Model> model = std::shared_ptr<core::Model>( new core::Model( core::AssimpLoader::loadModel(modelPath) ) );
    std::shared_ptr<core::Texture> texture = std::shared_ptr<core::Texture>( new core::Texture(texturePath));
    std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material(texture, modelVertexShader, textureShader));
    RenderableObject obj(name, position, parent, model, material);
    obj.transform.Scale(scale);
    return obj;
}







