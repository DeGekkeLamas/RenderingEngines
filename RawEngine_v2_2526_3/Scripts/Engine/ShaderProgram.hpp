#pragma once
#include "Shader.hpp"

class ShaderProgram {
    public:
    ShaderProgram(const Shader* shader);
    ShaderProgram(const Shader* shader, const Shader* shader2);

    unsigned int GetProgramID() const;
    private:
    unsigned int shaderProgram;
};


