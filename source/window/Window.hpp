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

    float m_screenWidth  = 1920.0f;
    float m_screenHeight = 1080.0f;



};