#pragma once

#include "buffer/Buffer.hpp"
#include "buffer/Texture.hpp"
#include "meshData.hpp"


namespace CrowEngine
{




class Mesh
{

public:

    Mesh() = default;
    ~Mesh() = default;

    inline void BindCurrentBuffer() { m_meshData.m_buffer.Bind(); }
    inline void UnbindCurrentBuffer() { m_meshData.m_buffer.Unbind(); }
    inline void BindCurrentTexture(){ m_meshData.m_texture.Bind(); }


    inline Buffer &GetCurrentBuffer(){ return m_meshData.m_buffer; }
    inline unsigned int GetTotalIndices(){ return m_meshData.m_buffer.GetTotalIndices(); }

    void Set();


private:


    MeshData m_meshData;

    //Buffer m_buffer;
    //Texture m_texture;

};


}

