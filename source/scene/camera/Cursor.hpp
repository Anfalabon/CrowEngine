#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

typedef struct Cursor
{

    double lastX = double(SCR_WIDTH) / 2.0f;
    double lastY = double(SCR_HEIGHT) / 2.0f;
    bool firstMouse = true;
    double yaw = 0.0f;
    double pitch = 0.0f;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    const float sensitivity = 0.1f;


}Cursor;


inline Cursor g_cursor; //and it's bad, i guess...


static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (g_cursor.firstMouse)
    {
        g_cursor.lastX = xpos;
        g_cursor.lastY = ypos;
        g_cursor.firstMouse = false;
    }

    float xoffset = xpos - g_cursor.lastX;
    float yoffset = g_cursor.lastY - ypos;
    g_cursor.lastX = xpos;
    g_cursor.lastY = ypos;

    //float sensitivity = 0.1f;
    xoffset *= g_cursor.sensitivity;
    yoffset *= g_cursor.sensitivity;

    g_cursor.yaw += xoffset;
    g_cursor.pitch += yoffset;

    if (g_cursor.pitch > 89.0f)
        g_cursor.pitch = 89.0f;
    if (g_cursor.pitch < -89.0f)
        g_cursor.pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(g_cursor.yaw)) * cos(glm::radians(g_cursor.pitch));
    direction.y = sin(glm::radians(g_cursor.pitch));
    direction.z = sin(glm::radians(g_cursor.yaw)) * cos(glm::radians(g_cursor.pitch));
    g_cursor.cameraFront = glm::normalize(direction);


}

