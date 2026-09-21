#pragma once

#include <glm/glm.hpp>

#include <string>


namespace CrowEngine
{


class Shader
{
public:

    Shader() = default;
    ~Shader() = default;

    void SetShader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

    inline unsigned int GetShaderProgramID(){ return m_shaderProgramID; }
    inline void UseProgram(){ glUseProgram(m_shaderProgramID); }


    //should these functions be static
    void SendMatrix4ToGpu(const char *uniformMatrix4Name, const glm::mat4 &matrix);
    void SendVec3ToGpu(const char *uniformVec3Name, const glm::vec3 &vec);
    void SendVec2ToGpu(const char *uniformVec2Name, const glm::vec2 &vec);
    void SendFloat1ToGpu(const char *uniformVec2Name, const float floatingPointNumber);


private:

    inline unsigned int GetUniformLocation(const char *uniformName)
    {
        return glGetUniformLocation(m_shaderProgramID, uniformName);
    }

    unsigned int m_shaderProgramID;

};



}

