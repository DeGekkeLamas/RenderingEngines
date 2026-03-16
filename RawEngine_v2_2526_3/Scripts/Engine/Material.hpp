#pragma once

#include "iostream"
#include "texture.h"
#include <map>#include "RenderableObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "assimpLoader.h"
#include "Camera.hpp"
#include "PointLight.hpp"

class Material {
public:
    Material(std::shared_ptr<core::Texture> texture, GLuint vertexShader, GLuint fragmentShader);
// Better OOP design:
    void Bind(); // activates the shader, and loads the uniforms (e.g. tint)
    std::shared_ptr<core::Texture> texture;
    GLuint fragmentShader;
    GLuint vertexShader;
    unsigned int* shaderProgram;
    void SetUniform(const std::string &uniformName, float toSet) const;
    void SetUniform(const std::string &uniformName, int toSet) const;
    void SetUniform(const std::string &uniformName, glm::vec3 toSet) const;
    void SetUniform(const std::string &uniformName, glm::vec4 toSet) const;
    void SetUniform(const std::string &uniformName, glm::mat4 toSet) const;
    void SetUniform(const std::string &uniformName, const GLuint texture, const int index) const;
private:
    static std::map< std::tuple<GLuint,GLuint> , unsigned int> existingShaderPrograms;
};
