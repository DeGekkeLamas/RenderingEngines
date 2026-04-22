#pragma once

#include "iostream"
#include "texture.h"
#include <map>
#include <glm/glm.hpp>

#include "assimpLoader.h"
#include "Shader.hpp"
#include "ShaderProgram.hpp"

class Material {
public:
    Material(std::shared_ptr<core::Texture> texture, Shader* vertexShader, Shader* fragmentShader);
// Better OOP design:
    void Bind(); // activates the shader, and loads the uniforms (e.g. tint)
    std::shared_ptr<core::Texture> texture;
    Shader* fragmentShader;
    Shader* vertexShader;
    ShaderProgram* shaderProgram;
    void SetUniform(const std::string &uniformName, float toSet) const;
    void SetUniform(const std::string &uniformName, int toSet) const;
    void SetUniform(const std::string &uniformName, glm::vec3 toSet) const;
    void SetUniform(const std::string &uniformName, glm::vec4 toSet) const;
    void SetUniform(const std::string &uniformName, glm::mat4 toSet) const;
    void SetUniform(const std::string &uniformName, const GLuint texture, const int index) const;
private:
    static std::map< std::tuple<Shader*,Shader*> , ShaderProgram*> existingShaderPrograms;
};
