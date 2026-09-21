#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace CrowEngine
{


class Camera
{

public:

    Camera()
    {
        m_projection = glm::perspective(glm::radians(45.0f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);

        m_position = glm::vec3(1.0f);
        m_right = glm::normalize(glm::cross(m_coordinateUp, m_front));
        m_up = glm::normalize(glm::cross(m_front, m_right));
    }

    ~Camera() = default;

    void ProcessInput(GLFWwindow* windowID);
    void UpdateCursor(GLFWwindow *windowID);
    void Update(GLFWwindow *windowID, const unsigned int shaderProgramID);

private:


    glm::vec3 m_position;
    glm::vec3 m_right;
    glm::vec3 m_up;
    glm::vec3 m_front;
    glm::vec3 m_target;

    const glm::vec3 m_coordinateUp = glm::vec3(0.0f, 1.0f, 0.0f);


    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);

    float m_cameraSpeed = 0.05f;

    //this should be taken from 'Window' class and should not be here

    float m_screenWidth = 1920.0f;
    float m_screenHeight = 1080.0f;



};






}


