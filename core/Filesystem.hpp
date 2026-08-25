#pragma once

#include <string>
#include <ctime>
#include <fstream>


#if defined(__cplusplus)
#include <filesystem>
#endif

#if defined(__linux__) || defined(__unix__)

#if defined(__cplusplus)
extern "C"{
#endif
    #include <sys/types.h>
    #include <sys/stat.h>
#if defined(__cplusplus)
}
#endif

#elif defined(__WIN32__) || defined(MSVC)
#include <sys/stat.h>
#endif






namespace CrowEngine
{


class FileWriter;
class FileReader;
class FileFormatConverter;


class Filesystem
{
public:

    enum WRITE_MODE
    {
        WRITE_AT_END,
        WRITE_AT_BEGINNING,
        WRITE_AT_SPECIFIC_POINT
    };

    Filesystem() = default;
    ~Filesystem() = default;

    static std::string ReadFileContent(const std::string &filePath);
    static void WriteContentToFile(const std::string &filePath, const std::string &content, WRITE_MODE placeToWrite = WRITE_AT_END);

    static std::time_t FileCreationTime(const std::string &filePath);
    static std::time_t FileLastModificationTime(const std::string &filePath);
    bool WasFileModified(const std::string &filePath);

private:
    std::time_t lastModificationTime = 0;
};


}
