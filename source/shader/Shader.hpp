#pragma once

#include <string>

class Shader
{
public:

    Shader() = default;
    ~Shader() = default;

    void SetShader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
    inline unsigned int GetShaderProgramID(){return m_shaderProgramID;}
    inline void UseProgram(){ glUseProgram(m_shaderProgramID); }

private:

    unsigned int m_shaderProgramID;

};