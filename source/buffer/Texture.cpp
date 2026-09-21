

#include <glad/glad.h>

#include "Texture.hpp"

#include <iostream>


namespace CrowEngine
{


void Texture::Load(const std::string &filePathStr)
{
    m_filePathStr = std::move(filePathStr);

    // load and generate the texture
    //int width, height, nrChannels;
    //std::cout << m_filePath << '\n';  //this causes bug


    std::cout << m_filePathStr.c_str() << '\n';
    //m_dataByte = reinterpret_cast<std::byte*>(stbi_load(m_filePathStr.c_str(), &m_width, &m_height, &m_nrChannels, 0));
    m_data = stbi_load(m_filePathStr.c_str(), &m_width, &m_height, &m_nrChannels, 0);
}



void Texture::Set(const bool enableOptions)
{


    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);


    if (enableOptions)
    {
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // // load and generate the texture
    // //int width, height, nrChannels;
    // //std::cout << m_filePath << '\n';  //this causes bug
    //
    //
    // std::cout << m_filePathStr.c_str() << '\n';
    // //m_dataByte = reinterpret_cast<std::byte*>(stbi_load(m_filePathStr.c_str(), &m_width, &m_height, &m_nrChannels, 0));
    // m_data = stbi_load(m_filePathStr.c_str(), &m_width, &m_height, &m_nrChannels, 0);

    //this->Load();
    if (m_data)
    {
        std::cout << m_width << '\n';
        std::cout << m_height << '\n';

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << '\n';
    }

    this->DeleteTexture();
}



void Texture::DeleteTexture()
{
    stbi_image_free(m_data);
}



}
