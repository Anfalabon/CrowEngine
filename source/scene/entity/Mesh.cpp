

#include "Mesh.hpp"
#include "assets/assetManager/AssetManager.hpp"


namespace CrowEngine
{


void Mesh::Set()
{
    //m_buffer.LoadBuffers("../../assets/classicCube/cubeVertices.txt", "../../assets/classicCube/cubeIndices.txt");
    //m_buffer.LoadBuffers(AssetManager::LoadMeshData("classicCube"));


    //i really don't know if using Singleton here is good. BTW the Singleton name helps a lot :)
    m_meshData.m_buffer.LoadBuffers(AssetManager::GetSingleton()->GetMeshData("classicCube"));
    m_meshData.m_buffer.SetBuffers();


    //the bug is here
    m_meshData.m_texture.Load("../../assets/images/grassTexture.jpg");
    m_meshData.m_texture.Set(true);
}



}