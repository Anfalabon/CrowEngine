

#include "Buffer.hpp"
#include "ModelLoader.hpp"

#include <utility>

Buffer::Buffer()
{
    auto bufferData = ModelLoader::LoadModel("", "");

    auto s1 = bufferData.first;
    auto s2  = bufferData.second;
}


void Buffer::SetBuffers()
{
    //unsigned int VAO;
    glGenVertexArrays(1, &m_VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

#define DEBUG
#ifdef DEBUG
    Buffer::CheckBuffer(m_vertices);
    Buffer::CheckBuffer(m_indices);
#endif

    //Start recording the current VAO
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Stop recording the current VAO
    glBindVertexArray(0);

    //return VAO;

}
