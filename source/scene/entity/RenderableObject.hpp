#pragma once


#include <glad/glad.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>

#include "Entity.hpp"
#include "Mesh.hpp"
#include "buffer/Buffer.hpp"
#include "buffer/Texture.hpp"


namespace CrowEngine
{


class RenderableObject //: public Entity
{

public:
    RenderableObject() = default;
    ~RenderableObject() = default;


    void Set();
    void Update(const unsigned int shaderProgramID);


    inline Mesh& GetMesh() { return m_mesh; } // Get a single Mesh(will implement for getting multiple meshes)

    // lol
    inline bool IsRenderable() { return m_isRenderable; }
    inline bool HasMesh() { return m_hasMesh; }

private:
    const bool m_isRenderable = true;
    const bool m_hasMesh = true;

    glm::mat4 m_model = glm::mat4(1.0f); // we should use 'Transform' instead


    Mesh m_mesh; // right now the Entity will have a single mesh

    // we will be doing this
    // std::vector<CrowEngine::Mesh> m_meshes;
};


} // namespace CrowEngine
