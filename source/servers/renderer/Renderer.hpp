#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.hpp"
#include "scene/Scene.hpp"
#include "scene/entity/RenderableObject.hpp"
#include "scene/entity/Mesh.hpp"

#include <unordered_map>

namespace CrowEngine
{



class Renderer
{

public:

    Renderer() = default;
    ~Renderer() = default;

    void SetRenderer();
    void Render(Scene &scene);

    inline Shader &GetShader(){ return m_shader; }
    inline unsigned int GetShaderID(){ return m_shader.GetShaderProgramID(); }

    static inline void GLDraw(Mesh &mesh, unsigned int primittiveType = GL_TRIANGLES)
    {
        glDrawElements(primittiveType, mesh.GetTotalIndices() , GL_UNSIGNED_INT, 0);
    }


private:

    Shader m_shader;  //this should be std::vector<Shader> as we wil be using shaders for rendering different things

    //std::unordered_map<std::string, Shader> m_shaders;


};


}   //namespace CrowEngine

