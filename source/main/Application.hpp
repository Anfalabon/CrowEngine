#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buffer/Buffer.hpp"
#include "window/Window.hpp"
#include "shader/Shader.hpp"
#include "servers/renderer/Renderer.hpp"
#include "window/Event.hpp"
#include "graphicsAPI/GraphicsAPI.hpp"
#include "Engine.hpp"

#include <iostream>





namespace CrowEngine
{


#ifdef __III___ //what is this lol


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) [[likely]]
    {
        glfwSetWindowShouldClose(window, true);
    }
}


static int RunGL()
{
    Window window;
    window.SetWindow();

#ifdef __glad_h_
    GraphicsAPI::LoadGLAD();
    //GraphicsAPI::LoadOpenGL();
#endif

    Renderer renderer;
    renderer.SetRenderer();

    Buffer rectangleBuffer;
    rectangleBuffer.SetBuffers();


    while(window.IsRunning())
    {
        processInput(window.GetID());

        //Event::OnWindowEscape(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //shader.UseProgram();
        renderer.GetShader().UseProgram();
        rectangleBuffer.Bind();

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        Renderer::GLDraw();

        //glBindVertexArray(0);

        glfwSwapBuffers(window.GetID());
        glfwPollEvents();
    }

    window.Terminate();
    return 1;

}
#endif


class Application
{
public:

    Application() = default;
    ~Application() = default;

    void Start()
    {
        m_engine.Set();
    }

    void Run()
    {
        m_engine.Run();
    }

    void Stop(){}   //will give the implementation later

private:

    Engine m_engine;

};



}
