#include "RenderableObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "PointLight.hpp"


RenderableObject::RenderableObject(const std::string &name, glm::vec3 position, Transform* parent,
                                   core::Model* model, Material* material) : GameObject(name, position, parent) {
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
    glUseProgram(material->shaderProgram);
    glUniformMatrix4fv(textureModelUniform, 1, GL_FALSE, glm::value_ptr(projection *
        view * transform.modelMatrix));
    glActiveTexture(GL_TEXTURE0);
    // Uniforms
    SetUniform("lightColor", light.color);
    SetUniform("lightPos", light.transform.position());
    SetUniform("camPos", camera.transform.position());
    SetUniform("lightStrength", light.intensity);
    SetUniform("modelMatrix", transform.modelMatrix);

    glBindTexture(GL_TEXTURE_2D, texture);

    model->render();
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void RenderableObject::Render(const GLuint texture) const {
    glUseProgram(material->shaderProgram);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture);

    model->render();
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}




void RenderableObject::SetUniform(const std::string &uniformName, const float toSet) const {
    const GLint uniformPos = glGetUniformLocation(material->shaderProgram, uniformName.c_str());
    glUniform1f(uniformPos, toSet);
}

void RenderableObject::SetUniform(const std::string &uniformName, const glm::vec3 toSet) const {
    const GLint uniformPos = glGetUniformLocation(material->shaderProgram, uniformName.c_str());
    glUniform3f(uniformPos, toSet.x,toSet.y,toSet.z);
}
void RenderableObject::SetUniform(const std::string &uniformName, const glm::vec4 toSet) const {
    const GLint uniformPos = glGetUniformLocation(material->shaderProgram, uniformName.c_str());
    glUniform4f(uniformPos, toSet.x,toSet.y,toSet.z, toSet.w);
}

void RenderableObject::SetUniform(const std::string &uniformName, glm::mat4 toSet) const {
    const GLint uniformPos = glGetUniformLocation(material->shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformPos, 1, GL_FALSE, glm::value_ptr(toSet));
}





