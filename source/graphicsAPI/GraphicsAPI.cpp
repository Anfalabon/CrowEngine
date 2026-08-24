

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GraphicsAPI.hpp"

#include <iostream>


int GraphicsAPI::LoadGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    return 1;
}


int GraphicsAPI::LoadValidationLayer()
{
    return -1;
}

int GraphicsAPI::LoadSDK()
{
    return -1;
}



