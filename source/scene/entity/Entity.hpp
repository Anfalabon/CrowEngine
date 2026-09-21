#pragma once


namespace CrowEngine
{

class Entity
{
public:

    Entity() = default;
    ~Entity() = default;

    virtual void Update() = 0;
    inline virtual bool IsRenderable() = 0;

private:

    unsigned int m_ID;
};


}




