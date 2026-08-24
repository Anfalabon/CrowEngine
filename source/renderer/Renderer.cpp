

#include "Renderer.hpp"

void Renderer::SetRenderer()
{
    shader.SetShader("../../source/shader/GLSL/vertexShader.vert.glsl",
                     "../../source/shader/GLSL/fragmentShader.frag.glsl");
}
