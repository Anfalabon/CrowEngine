

#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


#include "Camera.hpp"
#include "Cursor.hpp"

#include <iostream>
#include <core/Essentials.hpp>


namespace CrowEngine
{


void Camera::ProcessInput(GLFWwindow* windowID)
{
    if (glfwGetKey(windowID, GLFW_KEY_W) == GLFW_PRESS)
        m_position += m_cameraSpeed * m_front;
    if (glfwGetKey(windowID, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= m_cameraSpeed * m_front;
    if (glfwGetKey(windowID, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_cameraSpeed;
    if (glfwGetKey(windowID, GLFW_KEY_D) == GLFW_PRESS)
        m_position += glm::normalize(glm::cross(m_front, m_up)) * m_cameraSpeed;
}


void Camera::UpdateCursor(GLFWwindow* windowID)
{
    this->ProcessInput(windowID);
    glfwSetInputMode(windowID, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(windowID, mouse_callback);
}


void Camera::Update(GLFWwindow* windowID, const unsigned int shaderProgramID)
{
    // maybe we should put this in a different place
    // this->ProcessInput(windowID, m_position, m_front, m_up);
    this->UpdateCursor(windowID);

    m_front = g_cursor.cameraFront;

    m_right = glm::normalize(glm::cross(m_coordinateUp, m_front));
    m_up = glm::normalize(glm::cross(m_front, m_right));

    glm::vec3 target = m_position + m_front;
    m_view = glm::lookAt(m_position, target, m_up);


    LOG_MATRIX("View Matrix", m_view)
    LOG_MATRIX("Projection Matrix", m_projection)


    // these should be in Shader

    // glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE,
    //                    glm::value_ptr(glm::mat4(1.0f)));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE,
                       glm::value_ptr(m_projection));
}


} // namespace CrowEngine
