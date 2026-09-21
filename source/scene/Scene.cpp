

#include "Scene.hpp"


namespace CrowEngine
{


void Scene::Load()
{
    unsigned int staticallyLoadedEntities = 1;
    m_renderableObjects.reserve(staticallyLoadedEntities);
    //m_entities.reserve(staticallyLoadedEntities);

    for (unsigned int i = 0; i < staticallyLoadedEntities; ++i)
    {
        m_renderableObjects.push_back(RenderableObject());
        //m_entities.push_back(new RenderableObject());
        //m_uEntities.push_back(std::make_unique<Entity>(RenderableObject()));
    }

    for (unsigned int i = 0; i < staticallyLoadedEntities; ++i)
    {
        m_renderableObjects[i].Set();
    }

}


void Scene::Update(const unsigned int shaderProgramID)
{
    // for (unsigned int i = 0; i < m_entities.size(); ++i)
    // {
    //     m_entities[i]->Update();
    // }

    for (RenderableObject &renderableObject : m_renderableObjects)
    {
        renderableObject.Update(shaderProgramID);
    }

}



}
