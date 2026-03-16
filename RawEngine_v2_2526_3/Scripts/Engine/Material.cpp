#include "Material.hpp"
#include "iostream"
#include "texture.h"
#include "RenderableObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "assimpLoader.h"
#include "Camera.hpp"
#include "PointLight.hpp"
#include <map>

Material::Material(std::shared_ptr<core::Texture> texture, const GLuint vertexShader, GLuint fragmentShader) {
    this->texture = texture;
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;

    Bind();
}

void Material::Bind() {
    unsigned int* shaderProgram;
    std::tuple key(vertexShader, fragmentShader);
    if (existingShaderPrograms.contains(key))
    {
        shaderProgram = &existingShaderPrograms[key];
        printf("Shader already existed\n");
    }
    else
    {
        shaderProgram = new unsigned int(glCreateProgram());
        glAttachShader(*shaderProgram, vertexShader);
        glAttachShader(*shaderProgram, fragmentShader);
        glLinkProgram(*shaderProgram);
    }
    this->shaderProgram = shaderProgram;
}

std::map< std::tuple<GLuint,GLuint> , unsigned int> Material::existingShaderPrograms;


void Material::SetUniform(const std::string &uniformName, const float toSet) const {
    const GLint uniformPos = glGetUniformLocation(*shaderProgram, uniformName.c_str());
    glUniform1f(uniformPos, toSet);
}

void Material::SetUniform(const std::string &uniformName, const int toSet) const {
    const GLint uniformPos = glGetUniformLocation(*shaderProgram, uniformName.c_str());
    glUniform1i(uniformPos, toSet);
}


void Material::SetUniform(const std::string &uniformName, const glm::vec3 toSet) const {
    const GLint uniformPos = glGetUniformLocation(*shaderProgram, uniformName.c_str());
    glUniform3f(uniformPos, toSet.x,toSet.y,toSet.z);
}
void Material::SetUniform(const std::string &uniformName, const glm::vec4 toSet) const {
    const GLint uniformPos = glGetUniformLocation(*shaderProgram, uniformName.c_str());
    glUniform4f(uniformPos, toSet.x,toSet.y,toSet.z, toSet.w);
}

void Material::SetUniform(const std::string &uniformName, glm::mat4 toSet) const {
    const GLint uniformPos = glGetUniformLocation(*shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformPos, 1, GL_FALSE, glm::value_ptr(toSet));
}

void Material::SetUniform(const std::string& uniformName, const GLuint texture, const int index) const {
    glUseProgram(*shaderProgram);
    glActiveTexture(GL_TEXTURE0 + index);
    const GLint uniformPos = glGetUniformLocation(*shaderProgram, uniformName.c_str());
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(uniformPos, index);
}