#pragma once

#include <map>
#include "assimpLoader.h"

class Shader {
    public:
    Shader(const std::string &shaderPath, GLuint shaderType);
    GLuint GetShader() const;

private:
    GLuint shaderType;
    static std::string readFileToString(const std::string &filePath);
    static GLuint generateShader(const std::string &shaderPath, const GLuint shaderType);
    GLuint shader;
};