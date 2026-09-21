

#include "RenderableObject.hpp"
#include "shader/Shader.hpp"


namespace CrowEngine
{


void RenderableObject::Set()
{
    m_mesh.Set();
}


void RenderableObject::Update(const unsigned int shaderProgramID)
{
    //m_model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 10.0f));


    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
}


}