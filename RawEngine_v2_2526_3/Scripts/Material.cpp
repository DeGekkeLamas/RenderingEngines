#include "Material.hpp"
#include "iostream"
#include "texture.h"

Material::Material(core::Texture *texture, GLuint vertexShader, GLuint fragmentShader) {
    this->texture = texture;
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
}

void Material::Bind() {
    const unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, this->fragmentShader);
    glLinkProgram(shaderProgram);
    this->shaderProgram = shaderProgram;
}

