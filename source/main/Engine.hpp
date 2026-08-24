#pragma once

#include "buffer/Buffer.hpp"
#include "window/Window.hpp"
#include "shader/Shader.hpp"
#include "renderer/Renderer.hpp"
#include "window/Event.hpp"
#include "graphicsAPI/GraphicsAPI.hpp"


class Engine
{
public:

    Engine() = default;
    ~Engine() = default;

    void Set();
    void Update();
    void Run();

private:

    Window   m_window;
    Renderer m_renderer;
    Buffer   m_rectangleBuffer;

};