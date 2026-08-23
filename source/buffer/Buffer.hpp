#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>



inline std::vector<float> g_vertices = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f   // top left
};

inline std::vector<unsigned int> g_indices = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};




class Buffer
{
public:
    Buffer();
    ~Buffer() = default;

    void SetBuffers();
    inline unsigned int GetVAO(){ return m_VAO; }
    inline void Bind(){ glBindVertexArray(m_VAO); }

    template<typename T> static void CheckBuffer( const std::vector<T> &buffer );

private:

    unsigned int m_VAO;

    //do a Deep Copy
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

};





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
