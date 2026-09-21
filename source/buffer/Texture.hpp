#pragma once

#include <stb_image.h>

#include "core/Filesystem.hpp"


#include <iostream>
#include <string>



namespace CrowEngine
{


// //will not be using this right now
// typedef struct TextureAttributes
// {
//     int m_width;
//     int m_height;
//     int m_nrChannels;
//     std::string m_filePath;
//     unsigned char *m_data;
//
// }TextureAttributes;




class Texture
{

public:

    Texture()  = default;

    // Texture(const std::string &filePath) : m_filePathStr(filePath)
    // {
    //     bool catchValue = Filesystem::FoundFile(filePath);
    //     m_filePath = filePath.c_str();
    //
    //
    //     std::cout << m_filePath << '\n';
    // }

    ~Texture()
    {
        //free the image data we longer need it(cause the data was sent to the GPU storage(OpenGL server buffer storage))
        //stbi_image_free(m_data);
    }


    void Load(const std::string &filePathStr);
    void Set(const bool enableOptions = true);
    void DeleteTexture();

    inline void Bind(){ glBindTexture(GL_TEXTURE_2D, m_texture);}
    inline unsigned int GetTextureID(){ return m_texture; }


private:

    unsigned int m_texture;
    std::string m_filePathStr;  //may use std::string_view in the future
    const char *m_filePath;

    int m_width;
    int m_height;
    int m_nrChannels;
    unsigned char *m_data;
    std::byte *m_dataByte;

    //TextureAttributes m_textureInfo;
};




}



