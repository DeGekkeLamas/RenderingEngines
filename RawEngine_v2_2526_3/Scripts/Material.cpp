#include "Material.hpp"
#include "iostream"
#include "texture.h"
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