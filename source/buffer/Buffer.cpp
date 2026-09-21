

#include "Buffer.hpp"
#include "assets/assetManager/ModelLoader.hpp"
#include "assets/assetManager/AssetManager.hpp"

#include <utility>



namespace CrowEngine
{



// Buffer::Buffer(const std::string &verticesFilePath, const std::string &indicesFilePath)
// {
//     //std::pair<std::vector<float>, std::vector<unsigned int>> bufferData = ModelLoader::LoadModel("", "");
//
//     // verticesFilePath = "../../assets/rectangleVertices.txt";
//     // indicesFilePath  = "../../assets/rectangleIndices.txt";
//
//
//
//
//
//     // //auto bufferData = ModelLoader::LoadModel("../../assets/rectangleVertices.txt", "../../assets/rectangleIndices.txt");
//     // auto bufferData = ModelLoader::LoadModel(verticesFilePath, indicesFilePath);
//     //
//     // //idk if using std::move actaully optimizes the program here
//     // m_vertices = std::move(bufferData.first);
//     // m_indices  = std::move(bufferData.second);
// }



void Buffer::LoadBuffers(const std::string &verticesFilePath, const std::string &indicesFilePath)
{
    auto bufferData = ModelLoader::LoadModel(verticesFilePath, indicesFilePath);

    //idk if using std::move actaully optimizes the program here
    m_vertices = std::move(bufferData.first);
    m_indices  = std::move(bufferData.second);
}


void Buffer::LoadBuffers(const std::pair<std::vector<float>, std::vector<unsigned int>>& buffer)
{
    //auto bufferData = g_assetManager.GetMeshData("classicCube");

    m_vertices = std::move(buffer.first);
    m_indices  = std::move(buffer.second);
}


void Buffer::SetBuffers()
{
    //unsigned int VAO;
    glGenVertexArrays(1, &m_VAO);

    std::cout << "Is Running!" << '\n';

    //unsigned int m_VBO;
    glGenBuffers(1, &m_VBO);

    //unsigned int m_EBO;
    glGenBuffers(1, &m_EBO);

//#define DEBUG
#ifdef DEBUG
    Buffer::CheckBuffer(m_vertices);
    Buffer::CheckBuffer(m_indices);
#endif

    //Start recording the current VAO
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);




    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Stop recording the current VAO
    glBindVertexArray(0);

    //return VAO;

}




}


