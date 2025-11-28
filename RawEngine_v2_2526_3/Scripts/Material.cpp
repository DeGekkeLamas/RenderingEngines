#include "Material.hpp"
#include "iostream"
#include "texture.h"

Material::Material(core::Texture *texture, const GLuint vertexShader, GLuint fragmentShader) {
    this->texture = texture;
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
}

void Material::Bind() {
    const unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    this->shaderProgram = shaderProgram;
}

