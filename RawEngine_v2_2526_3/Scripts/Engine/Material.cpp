#include "Material.hpp"
#include "iostream"
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "assimpLoader.h"
#include <map>


Material::Material(std::shared_ptr<core::Texture> texture, Shader* vertexShader, Shader* fragmentShader) {
    this->texture = texture;
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;

    Bind();
}

void Material::Bind() {
    ShaderProgram* shaderProgram;
    std::tuple key(vertexShader, fragmentShader);
    if (existingShaderPrograms.contains(key))
    {
        shaderProgram = existingShaderPrograms[key];
        printf("Shader already existed\n");
    }
    else
    {
        shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    }
    this->shaderProgram = shaderProgram;
}

std::map< std::tuple<Shader*,Shader*> , ShaderProgram*> Material::existingShaderPrograms;


void Material::SetUniform(const std::string &uniformName, const float toSet) const {
    shaderProgram->SetUniform(uniformName, toSet);
}
void Material::SetUniform(const std::string &uniformName, const int toSet) const {
    shaderProgram->SetUniform(uniformName, toSet);
}
void Material::SetUniform(const std::string &uniformName, const glm::vec3 toSet) const {
    shaderProgram->SetUniform(uniformName, toSet);
}
void Material::SetUniform(const std::string &uniformName, const glm::vec4 toSet) const {
    shaderProgram->SetUniform(uniformName, toSet);
}

void Material::SetUniform(const std::string &uniformName, glm::mat4 toSet) const {
    shaderProgram->SetUniform(uniformName, toSet);
}
void Material::SetUniform(const std::string& uniformName, const GLuint texture, const int index) const {
    shaderProgram->SetUniform(uniformName, texture, index);
}