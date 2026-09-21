

#include "Renderer.hpp"
#include "core/Filesystem.hpp"


namespace CrowEngine
{



void Renderer::SetRenderer()
{

    std::string vertexShaderFilePath = "../../source/shader/GLSL/vertexShader.vert.glsl";
    std::string fragmentShaderFilePath = "../../source/shader/GLSL/fragmentShader.frag.glsl";

#define __LOGGING__ //define loggin locally
#ifdef __LOGGING__
    Filesystem::FoundFile(vertexShaderFilePath);
    Filesystem::FoundFile(fragmentShaderFilePath);
#endif

    m_shader.SetShader(vertexShaderFilePath, fragmentShaderFilePath);

}


void Renderer::Render(Scene &scene)
{
    //if(m_shaderNotSet){ m_shader.SetShader(); }

    m_shader.UseProgram();

    for (unsigned int i = 0; i < scene.GetTotalRenderables(); ++i)
    {
        //Renderer::GLDraw();
        //scene.GetEntity(i)->
        // if (scene.GetEntity(i)->IsRenderable())
        // {
        //     //scene.GetEntity(i)->GetMesh()
        // }

        Renderer::GLDraw(scene.GetRenderableObject(i).GetMesh(), GL_TRIANGLES);

    }


}




}


