#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.hpp"


class Renderer
{

public:
    Renderer() = default;
    ~Renderer() = default;

    void SetRenderer();
    void Render(){}

    inline Shader &GetShader(){ return shader; }
    inline unsigned int GetShaderID(){ return shader.GetShaderProgramID(); }

    static inline void GLDraw()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

private:

    Shader shader;

};