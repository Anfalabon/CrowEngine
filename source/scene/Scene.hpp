#pragma once

#include "entity/RenderableObject.hpp"
#include "entity/Entity.hpp"

#include <vector>







namespace CrowEngine
{


class Scene
{

public:

    Scene() = default;
    ~Scene() = default;

    void Load();
    void Update(const unsigned int shaderProgramID);

    inline RenderableObject &GetRenderableObject(const unsigned int index)
    {
        if (index < 0 || index >= m_renderableObjects.size())
        {

            //m_renderableObjects.at()
        }
        return m_renderableObjects[index];
    }

    inline unsigned int GetTotalRenderables(){ return static_cast<unsigned int>(m_renderableObjects.size()); }

    // inline Entity *GetEntity(const unsigned int index)
    // {
    //     if (index < 0 || index >= m_entities.size())
    //     {
    //
    //     }
    //     return m_entities[index];
    // }


    //inline unsigned int GetTotalEntities(){ return static_cast<unsigned int>(m_entities.size()); }
    //inline std::vector<Entity*> GetEntities(){ return m_entities; }




private:

    std::vector<RenderableObject> m_renderableObjects;
    //std::vector<Entity*> m_entities;
    //std::vector<std::unique_ptr<Entity>> m_uEntities;
    //std::vector<RenderableObject> m_renderableObjects;

};


}



