

#include "core/Filesystem.hpp"

#include <iostream>
#include <filesystem>
#include <vector>
#include <utility>


static void GetBufferFromFile()
{

}

static void LoadModel(const std::string &verticesFilePath, const std::string &indicesFilePath)
{

    //we need to optimize to here
    std::string verticesFileContent = CrowEngine::Filesystem::ReadFileContent(verticesFilePath);
    std::string indicesFileContent = CrowEngine::Filesystem::ReadFileContent(indicesFilePath);

    std::vector<float> vertices{};
    std::vector<unsigned int> indices{};


    verticesFileContent.push_back(',');
    verticesFileContent.push_back('*');


    std::string temp = "";
    std::size_t i = 0;
    //while ( verticesFileContent[i] != '*' )
    while ( verticesFileContent[i] != '*' )
    {

        temp += verticesFileContent[i];
        ++i;

        if (verticesFileContent[i] == ',')
        {
            //should be doing reserve for memory optimization
            vertices.push_back(std::stof(temp));
            temp = "";
            ++i;
        }

    }

    std::cout << "Hit The End: " << i <<'\n';


    for (auto vertex : vertices)
    {
        std::cout << vertex << "," << '\n';
    }

}



int main()
{
    // std::string str = "     -0.5f";
    // float strFloat = std::stof(str);
    //
    // std::cout << strFloat + 0.9f << '\n';

    LoadModel("../../asset/rectangleVertices.txt", "../../asset/rectangleIndices.txt");

    return 0;
}