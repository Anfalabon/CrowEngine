#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:

    Window() = default;
    ~Window() = default;

    int SetWindow();
    inline GLFWwindow *GetID(){ return m_windowID; }
    inline void Terminate(){ glfwTerminate(); }
    inline bool IsRunning(){ return !glfwWindowShouldClose(m_windowID); }

    void OnKeyPressed();

private:

    GLFWwindow *m_windowID;

};