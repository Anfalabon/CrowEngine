#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Event
{

public:

    Event() = default;
    ~Event() = default;

    static inline void OnWindowEscape(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) [[unlikely]]
        {
            glfwSetWindowShouldClose(window, true);
        }
    }



private:

};