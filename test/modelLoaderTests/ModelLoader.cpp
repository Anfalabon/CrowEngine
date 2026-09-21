

#include "gtest/gtest.h"
//#include "spdlog/spdlog.h"

#include "core/Filesystem.hpp"

#include <vector>
#include <utility>





using VertexPosition = float;
using Index = unsigned int;

template<typename T> static std::vector<T> LoadBuffer(const std::string &bufferFilePath)
{
    std::string bufferFileContent = CrowEngine::Filesystem::ReadFileContent(bufferFilePath);

    if (bufferFileContent.length() == 0)
    {
        return std::vector<T>{};
    }

    std::vector<T> buffer{};

    bufferFileContent.push_back(',');
    bufferFileContent.push_back('*');

    //bool isTypeFloat = std::is_same<T, float>::value;

    std::string temp = "";
    std::size_t i = 0;

    while ( bufferFileContent.at(i) != '*' )
    {
        temp += bufferFileContent.at(i);
        ++i;

        if (bufferFileContent.at(i) == ',')
        {
            //should be doing reserve for memory optimization
            if constexpr(std::is_same<T, float>::value)
            {
                buffer.push_back(std::stof(temp));
            }
            else if constexpr(std::is_same<T, unsigned int>::value)
            {
                buffer.push_back(std::stoi(temp));
            }

            //std::is_same<T, float>::value? buffer.push_back(std::stof(temp)) : buffer.push_back(std::stoi(temp));

            temp = "";
            ++i;
        }
    }

    return buffer;


}


#ifdef NOT_GENERIC
static void LoadModel(const std::string &verticesFilePath, const std::string &indicesFilePath)
{

    //TODO: we need to optimize to here
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

#endif



namespace TestData
{

inline std::vector<VertexPosition> g_testVertices{
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

inline std::vector<Index> g_testIndices{
    0, 1, 3,
    1, 2, 3
};


}


TEST(verticesTest, handlesInvalidVertices)
{
    EXPECT_EQ(LoadBuffer<VertexPosition>("../../../assets/rectangleVertices.txt"), TestData::g_testVertices);
}

TEST(indicesTest, handlesInvalidIndicesSize)
{
    EXPECT_EQ(LoadBuffer<Index>("../../../assets/rectangleIndices.txt"), TestData::g_testIndices);
}


int main(int argc, char **argv)
{
    // std::string str = "     -0.5f";
    // float strFloat = std::stof(str);
    //
    // std::cout << strFloat + 0.9f << '\n';

    //LoadModel("../../../assets/rectangleVertices.txt", "../../../assets/rectangleIndices.txt");


    //ASSERT_EQ(LoadBuffer<VertexPosition>("../../../assets/rectangleVertices.txt"), g_testVertices);

    testing::InitGoogleTest(&argc, argv);   //these argc, argc are not necessary here. See the documentation

    return RUN_ALL_TESTS();

}