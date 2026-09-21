#include <glad/glad.h>

#include "Texture.hpp"

#include <vector>


namespace CrowEngine
{

    typedef struct MeshData
    {

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

        Texture m_texture;

    } MeshData;

} // namespace CrowEngine
