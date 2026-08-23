

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buffer/Buffer.hpp"
#include "window/Window.hpp"

#include <iostream>

#include "shader/Shader.hpp"
#include "renderer/Renderer.hpp"



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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader;
    shader.SetShader("../../source/shader/GLSL/vertexShader.vert.glsl",
                     "../../source/shader/GLSL/fragmentShader.frag.glsl");

    Buffer rectangleBuffer;
    rectangleBuffer.SetBuffers();


    while(window.IsRunning())
    {
        processInput(window.GetID());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.UseProgram();
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

int main()
{
    return static_cast<int>(RunGL());
}