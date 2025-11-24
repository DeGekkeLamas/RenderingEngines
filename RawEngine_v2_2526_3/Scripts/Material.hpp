#pragma once
#include "iostream"
#include "texture.h"

class Material {
public:
    Material(core::Texture* texture, GLuint shader);
// Better OOP design:
    //void Bind(); // activates the shader, and loads the uniforms (e.g. tint)
//private:
    core::Texture* texture;
    GLuint shader;
};
