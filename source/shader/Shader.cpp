#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>


#include "core/Filesystem.hpp"
#include "Shader.hpp"

#include <iostream>


namespace CrowEngine
{


void Shader::SetShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    auto vertexShaderSource = CrowEngine::Filesystem::ReadFileContent(vertexShaderFilePath);
    auto fragmentShaderSource = CrowEngine::Filesystem::ReadFileContent(fragmentShaderFilePath);


    std::clog << vertexShaderSource << '\n';
    std::clog << fragmentShaderSource << '\n';


    const char* vertexShaderSourceStr = vertexShaderSource.c_str();
    const char* fragmentShaderSourceStr = fragmentShaderSource.c_str();

    //spdlog::logger::info("Hello, Shader!");


    //setting vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSourceStr, NULL);
    glCompileShader(vertexShader);

    int isVertSuccess;
    char vertInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isVertSuccess);
    if (!isVertSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertInfoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertInfoLog << '\n';
    }


    //setting fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSourceStr, NULL);
    glCompileShader(fragmentShader);

    int isFragSuccess;
    char fragInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isFragSuccess);
    if (!isFragSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, fragInfoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragInfoLog << '\n';
    }


    //setting shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    //delete the individual shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //return shaderProgram;
    m_shaderProgramID = shaderProgram;
}



void Shader::SendMatrix4ToGpu(const char *uniformMatrix4Name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(this->GetUniformLocation(uniformMatrix4Name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::SendVec3ToGpu(const char *uniformVec3Name, const glm::vec3 &vec)
{
    glUniform3fv(this->GetUniformLocation(uniformVec3Name), 1, glm::value_ptr(vec));
}


void Shader::SendVec2ToGpu(const char *uniformVec2Name, const glm::vec2 &vec)
{
    glUniform3fv(this->GetUniformLocation(uniformVec2Name), 1, glm::value_ptr(vec));
}


void Shader::SendFloat1ToGpu(const char *uniformFloat1Name, const float floatingPointNumber)
{
    glUniform1f(this->GetUniformLocation(uniformFloat1Name), floatingPointNumber);
}





}   //namespace CrowEngine
