#pragma once
#include "Shader.hpp"

class ShaderProgram {
    public:
    ShaderProgram(const Shader* shader);
    ShaderProgram(const Shader* shader, const Shader* shader2);

    // Uniforms
    GLint GetUniformLocation(const std::string &uniformName) const;
    void SetUniform(const std::string &uniformName, const float toSet) const;
    void SetUniform(const std::string &uniformName, const int toSet) const;
    void SetUniform(const std::string &uniformName, const glm::vec3 toSet) const;
    void SetUniform(const std::string &uniformName, const glm::vec4 toSet) const;
    void SetUniform(const std::string &uniformName, const glm::mat4 toSet) const;
    void SetUniform(const std::string &uniformName, const GLuint texture, const int index) const;
    static void SetUniform(const GLint uniformPos, const float toSet);
    static void SetUniform(const GLint uniformPos, const int toSet);
    static void SetUniform(const GLint uniformPos, const glm::vec3 toSet);
    static void SetUniform(const GLint uniformPos, const glm::vec4 toSet);
    static void SetUniform(const GLint uniformPos, const glm::mat4 toSet);
    static void SetUniform(const GLint uniformPos, const GLuint texture, const int index);

    unsigned int GetProgramID() const;
    private:
    unsigned int shaderProgram;
};


