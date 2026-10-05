#pragma once

//#include "scene/entity/meshData.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <filesystem>
#include <memory>


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


    static std::shared_ptr<std::filesystem::path> ExecutableDir()
    {
        return std::make_shared<std::filesystem::path>(std::filesystem::read_symlink("/proc/self/exe").parent_path());
    }

public:

    static const std::filesystem::path m_resourcesDir;

private:

    std::unordered_map<std::string, std::pair<std::vector<float>, std::vector<unsigned int>>> m_meshData;
    //std::unordered_map<std::string, MeshData> m_meshD;



};




} // namespace CrowEngine
