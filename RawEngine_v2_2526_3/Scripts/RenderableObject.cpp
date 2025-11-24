#include "RenderableObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


RenderableObject::RenderableObject(const std::string &name, glm::vec3 position, Transform* parent,
    core::Model* model, Material* material) : GameObject(name, position, parent) {
    this->model = model;
    this->material = material;
}

void RenderableObject::Render(const glm::mat4 &view, const glm::mat4 &projection, const GLint textureModelUniform) {

    glUseProgram(material->shaderProgram);
    glUniformMatrix4fv(textureModelUniform, 1, GL_FALSE, glm::value_ptr(projection *
        view * transform.modelMatrix));
    glActiveTexture(GL_TEXTURE0);
    // glUniform1i(textureUniform, 0);
    GLint lightposUniform = glGetUniformLocation(material->shaderProgram, "lightPos"); // Light pos
    glUniform3f(lightposUniform, 1,1,0);
    GLint worldPosUniform = glGetUniformLocation(material->shaderProgram, "modelMatrix"); // Matrix
    glUniformMatrix4fv(worldPosUniform, 1, GL_FALSE, glm::value_ptr(transform.modelMatrix));

    if (material->texture != nullptr) {
        glBindTexture(GL_TEXTURE_2D, material->texture->getId());
    }
    model->render();
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

