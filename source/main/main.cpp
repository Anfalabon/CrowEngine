

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buffer/Buffer.hpp"
#include "window/Window.hpp"

#include <iostream>

#include "shader/Shader.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    Buffer triangleBuffer;
    triangleBuffer.SetBuffers();


    while(!glfwWindowShouldClose(window.GetWindowID()))
    {
        processInput(window.GetWindowID());

        glUseProgram(shader.GetShaderProgramID());
        glBindVertexArray(triangleBuffer.GetVAO());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.GetWindowID());
        glfwPollEvents();
    }

    glfwTerminate();
    return 1;

}

int main()
{
    return static_cast<int>(RunGL());
}