
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "core/Filesystem.hpp"
#include "Shader.hpp"

#include <iostream>


void Shader::SetShader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
{
    auto vertexShaderSource = Synapse::Filesystem::ReadFileContent(vertexShaderFilePath);
    auto fragmentShaderSource = Synapse::Filesystem::ReadFileContent(fragmentShaderFilePath);

    std::clog << vertexShaderSource << '\n';
    std::clog << fragmentShaderSource << '\n';


    const char *vertexShaderSourceStr = vertexShaderSource.c_str();
    const char *fragmentShaderSourceStr = fragmentShaderSource.c_str();

    //spdlog::logger::info("");



    //setting vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSourceStr, NULL);
    glCompileShader(vertexShader);

    int  isVertSuccess;
    char vertInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isVertSuccess);
    if(!isVertSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertInfoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertInfoLog << '\n';
    }



    //setting fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSourceStr, NULL);
    glCompileShader(fragmentShader);

    int  isFragSuccess;
    char fragInfoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isFragSuccess);
    if(!isFragSuccess)
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