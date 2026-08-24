#pragma once

class GraphicsAPI
{
public:

    GraphicsAPI() = default;
    ~GraphicsAPI() = default;

    static int LoadGLAD(); //for OpenGL
    static int LoadValidationLayer(); //for Vulkan
    static int LoadSDK(); //for DirectX

private:

};