#pragma once

//#include "scene/entity/meshData.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <filesystem>


namespace CrowEngine
{


class AssetManager
{

public:



    AssetManager() = default;
    ~AssetManager() = default;

    void SetAssets();
    inline std::string GetAsset(const std::string& assetName) { return std::string{}; } // for now it gives nothing
    std::pair<std::vector<float>, std::vector<unsigned int>> GetMeshData(const std::string& assetName)
    {
        return m_meshData[assetName];
    }

    static AssetManager* GetSingleton()
    {
        static AssetManager assetManager;
        assetManager.SetAssets();
        return &assetManager;
    }



    static std::filesystem::path ResourceAbsolutePath()
    {
        return std::filesystem::current_path().root_directory();
    }

private:

    std::unordered_map<std::string, std::pair<std::vector<float>, std::vector<unsigned int>>> m_meshData;
    //std::unordered_map<std::string, MeshData> m_meshD;


};




} // namespace CrowEngine
