

#include "AssetManager.hpp"
#include "ModelLoader.hpp"


namespace CrowEngine
{


    void AssetManager::SetAssets()
    {

        // m_meshD["classicCube"] =
        // m_assets["classicCube"] = "";

        // m_meshDataPath["classicCube"] = std::make_pair("../../assets/classicCube/cubeVertices.txt",
        // "../../assets/classicCube/cubeIndices.txt");

        m_meshData["classicCube"] = ModelLoader::LoadModel("../../assets/classicCube/cubeVertices.txt",
                                                           "../../assets/classicCube/cubeIndices.txt");
    }


} // namespace CrowEngine
