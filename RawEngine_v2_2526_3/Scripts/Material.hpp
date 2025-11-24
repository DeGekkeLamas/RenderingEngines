#pragma once
#include "iostream"
#include "texture.h"

class Material {
public:
    Material(core::Texture* texture, GLuint vertexShader, GLuint fragmentShader);
// Better OOP design:
    void Bind(); // activates the shader, and loads the uniforms (e.g. tint)
// private:
    core::Texture* texture;
    GLuint fragmentShader;
    GLuint vertexShader;
    unsigned int shaderProgram;
};
