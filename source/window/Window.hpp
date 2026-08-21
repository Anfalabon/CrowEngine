#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:

    Window() = default;
    ~Window() = default;

    int SetWindow();
    inline GLFWwindow *GetWindowID(){return m_windowID;}

private:

    GLFWwindow *m_windowID;

};