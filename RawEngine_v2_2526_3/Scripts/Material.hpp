#pragma once
#include "iostream"
#include "texture.h"

class Material {
public:
    Material(core::Texture* texture, GLuint shader);
    core::Texture* texture;
    GLuint shader;
};
