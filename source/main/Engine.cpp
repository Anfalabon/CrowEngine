

#include "Engine.hpp"

#include "buffer/Buffer.hpp"

void Engine::Update()
{
    //shader.UseProgram();
    m_renderer.GetShader().UseProgram();
    m_rectangleBuffer.Bind();
}


void Engine::Run()
{

    while(m_window.IsRunning())
    {
        //processInput(m_window.GetID());

        m_window.OnKeyPressed();

        //Event::OnWindowEscape(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->Update();

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        Renderer::GLDraw();

        //glBindVertexArray(0);

        glfwSwapBuffers(m_window.GetID());
        glfwPollEvents();
    }

    m_window.Terminate();

}


void Engine::Set()
{
    m_window.SetWindow();

#ifdef __glad_h_
    GraphicsAPI::LoadGLAD();
    //GraphicsAPI::LoadOpenGL();
#endif

    m_renderer.SetRenderer();

    m_rectangleBuffer.SetBuffers();

}