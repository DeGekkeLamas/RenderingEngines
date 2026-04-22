#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>

unsigned int ShaderProgram::GetProgramID() const {
    return shaderProgram;
}

ShaderProgram::ShaderProgram(const Shader* shader) {
    shaderProgram = glCreateProgram();
    int success;
    char infoLog[512];

    glAttachShader(shaderProgram, shader->GetShader());
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Error! Making Shader Program: %s\n", infoLog);
    }
}

ShaderProgram::ShaderProgram(const Shader* shader, const Shader* shader2) {
    shaderProgram = glCreateProgram();
    int success;
    char infoLog[512];

    glAttachShader(shaderProgram, shader->GetShader());
    glAttachShader(shaderProgram, shader2->GetShader());
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Error! Making Shader Program: %s\n", infoLog);
    }
}
GLuint ShaderProgram::GenerateStorageBuffer(const int index, const int n) {
    GLuint buffer;
    glGenBuffers(n, &buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, buffer);
    return buffer;
}

GLint ShaderProgram::GetUniformLocation(const std::string &uniformName) const {
    return glGetUniformLocation(shaderProgram, uniformName.c_str());
}
void ShaderProgram::SetUniform(const std::string &uniformName, const float toSet) const {
    const GLint uniformPos = GetUniformLocation(uniformName.c_str());
    SetUniform(uniformPos, toSet);
}
void ShaderProgram::SetUniform(const std::string &uniformName, const int toSet) const {
    const GLint uniformPos = GetUniformLocation(uniformName.c_str());
    SetUniform(uniformPos, toSet);
}
void ShaderProgram::SetUniform(const std::string &uniformName, const glm::vec3 toSet) const {
    const GLint uniformPos = GetUniformLocation(uniformName.c_str());
    SetUniform(uniformPos, toSet);
}
void ShaderProgram::SetUniform(const std::string &uniformName, const glm::vec4 toSet) const {
    const GLint uniformPos = GetUniformLocation(uniformName.c_str());
    SetUniform(uniformPos, toSet);
}

void ShaderProgram::SetUniform(const std::string &uniformName, const glm::mat4 toSet) const {
    const GLint uniformPos = GetUniformLocation(uniformName.c_str());
    SetUniform(uniformPos, toSet);
}
void ShaderProgram::SetUniform(const std::string& uniformName, const GLuint texture, const int index) const {
    glUseProgram(shaderProgram);
    glActiveTexture(GL_TEXTURE0 + index);
    const GLint uniformPos = GetUniformLocation(uniformName.c_str());
    SetUniform(uniformPos, texture, index);
}
void ShaderProgram::SetUniform(const GLint uniformPos, const float toSet) {
    glUniform1f(uniformPos, toSet);
}
void ShaderProgram::SetUniform(const GLint uniformPos, const int toSet) {
    glUniform1i(uniformPos, toSet);
}
void ShaderProgram::SetUniform(const GLint uniformPos, glm::vec3 toSet) {
    glUniform3f(uniformPos, toSet.x,toSet.y,toSet.z);
}
void ShaderProgram::SetUniform(const GLint uniformPos, glm::vec4 toSet) {
    glUniform4f(uniformPos, toSet.x,toSet.y,toSet.z, toSet.w);
}
void ShaderProgram::SetUniform(const GLint uniformPos, glm::mat4 toSet) {
    glUniformMatrix4fv(uniformPos, 1, GL_FALSE, glm::value_ptr(toSet));
}
void ShaderProgram::SetUniform(const GLint uniformPos, const GLuint texture, const int index) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(uniformPos, index);
}
