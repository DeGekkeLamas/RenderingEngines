#include "Material.hpp"
#include "iostream"
#include "texture.h"

Material::Material(core::Texture *texture, GLuint shader) {
    this->texture = texture;
    this->shader = shader;
}
