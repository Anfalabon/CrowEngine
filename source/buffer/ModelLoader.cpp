

#include <vector>

#include "ModelLoader.hpp"
#include "core/Filesystem.hpp"



std::pair<std::vector<float>, std::vector<unsigned int>> LoadModel(const std::string &verticesFilePath,
                                         const std::string &indicesFilePath)
{
    //we need to optimize to here
    std::string verticesFileContent = Synapse::Filesystem::ReadFileContent(verticesFilePath);
    std::string indicesFileContent  = Synapse::Filesystem::ReadFileContent(indicesFilePath);

    return std::make_pair(ModelLoader::GetBufferFromFile<float>(verticesFileContent),
                          ModelLoader::GetBufferFromFile<unsigned int>(indicesFileContent));
}

