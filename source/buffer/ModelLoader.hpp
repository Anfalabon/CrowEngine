#pragma once

#include <utility>
#include <string>
#include <vector>
#include <type_traits>


class ModelLoader
{
public:

    ModelLoader() = default;
    ~ModelLoader() = default;

    template<typename T> static std::vector<T> GetBufferFromFile(std::string &bufferContentString);
    static std::pair<std::vector<float>, std::vector<unsigned int>> LoadModel(const std::string &verticesFilePath,
                                                                              const std::string &indicesFilePath);

private:

};



template<typename T> std::vector<T> ModelLoader::GetBufferFromFile(std::string &bufferContentString)
{
    std::vector<T> buffer;

    if (bufferContentString[bufferContentString.size() - 1] != '*')
    {
        bufferContentString.push_back(',');
        bufferContentString.push_back('*');
    }



    std::string temp = "";
    std::size_t i = 0;
    while ( bufferContentString[i] != '*' )
    {
        temp += bufferContentString[i];
        ++i;

        if (bufferContentString[i] == ',')
        {
            //should be doing reserve for memory optimization
            //also the size of the buffer vector is indeed smaller or equal than the size of the bufferContentString itself

            if constexpr (std::is_same<T, float>::value)
            {
                buffer.push_back(std::stof(temp));
            }
            else if constexpr (std::is_same<T, unsigned int>::value)
            {
                buffer.push_back(std::stoi(temp));
            }
            else  [[unlikely]]
            {

            }

            temp = "";
            ++i;
        }
    }

    return buffer;

}
