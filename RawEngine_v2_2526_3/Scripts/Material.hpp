#pragma once

#include "iostream"
#include "texture.h"
#include <map>

class Material {
public:
    Material(core::Texture* texture, GLuint vertexShader, GLuint fragmentShader);
// Better OOP design:
    void Bind(); // activates the shader, and loads the uniforms (e.g. tint)
    core::Texture* texture;
    GLuint fragmentShader;
    GLuint vertexShader;
    unsigned int* shaderProgram;
private:
    static std::map< std::tuple<GLuint,GLuint> , unsigned int> existingShaderPrograms;
};
