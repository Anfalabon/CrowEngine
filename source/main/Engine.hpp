#pragma once

#include "buffer/Buffer.hpp"
#include "window/Window.hpp"
#include "shader/Shader.hpp"
#include "servers/renderer/Renderer.hpp"
#include "window/Event.hpp"
#include "graphicsAPI/GraphicsAPI.hpp"
#include "scene/camera/Camera.hpp"
#include "scene/Scene.hpp"



namespace CrowEngine
{



class Engine
{
public:

    Engine() = default;
    ~Engine() = default;

    void Set();
    void Update();
    void Run();

private:

    Window              m_window;
    Renderer            m_renderer;
    Camera              m_camera;
    Scene               m_scene;
    //RenderableObject    m_renderableObject;


};



}

