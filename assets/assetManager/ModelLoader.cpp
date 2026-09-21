

#include <vector>

#include "ModelLoader.hpp"
#include "core/Filesystem.hpp"



std::pair<std::vector<float>, std::vector<unsigned int>> ModelLoader::LoadModel(const std::string &verticesFilePath,
                                                                                const std::string &indicesFilePath)
{
    //we need to optimize here
    std::string verticesFileContent = CrowEngine::Filesystem::ReadFileContent(verticesFilePath);
    std::string indicesFileContent  = CrowEngine::Filesystem::ReadFileContent(indicesFilePath);

    return std::make_pair(ModelLoader::GetBufferFromFile<float>(verticesFileContent),
                          ModelLoader::GetBufferFromFile<unsigned int>(indicesFileContent));
}

