#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>



//in CLion how do we select and then move the cursor to a specific line to select the whole portion?

namespace CrowEngine
{


class Buffer
{
public:

    Buffer() = default;
    //Buffer(const std::string &verticesFilePath, const std::string &indicesFilePath);

    ~Buffer()
    {
        //glDeleteVertexArrays(1, &m_VAO);
    }

    void LoadBuffers(const std::string &verticesFilePath, const std::string &indicesFilePath);
    void LoadBuffers(const std::pair<std::vector<float>, std::vector<unsigned int>> &buffer);
    void SetBuffers();

    inline unsigned int GetVAO(){ return m_VAO; }
    inline void Bind(){ glBindVertexArray(m_VAO); }
    inline void Unbind(){ glBindVertexArray(0); }
    inline unsigned int GetTotalIndices(){ return static_cast<unsigned int>(m_indices.size()); }

    template<typename T> static void CheckBuffer( const std::vector<T> &buffer );

private:

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

};



//put it in another File

template<typename T> void Buffer::CheckBuffer( const std::vector<T> &buffer )
{
    if (buffer.empty())
    {
        std::clog << "The buffer is empty!" << '\n';
        return;
    }

    for (auto element : buffer)
    {
        std::cout << element << " ";
    }

    std::cout << "\n";
}




}


