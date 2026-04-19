#include "ShaderProgram.hpp"

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
