#include "Filesystem.hpp"

#include <iostream>



//TODO: change the namespace Synapse to CrowEngine/Crow
namespace CrowEngine
{



std::string Filesystem::ReadFileContent(const std::string &filePath)
{
    std::ifstream inputFileStream(filePath);

    if(inputFileStream.fail())
    {
        std::cout << "didn't find file!" << '\n';
        std::cout << "File name: " << filePath << '\n';
        //std::cin.get();    //this is definately bad for doing
        return "";
    }

    std::string fileContent = "";

    std::string fileLine;
    while ( std::getline(inputFileStream, fileLine) )
        fileContent += fileLine + '\n';

    inputFileStream.close();

    return fileContent;
}


//these two are empty functions for now(no implementation)
void Filesystem::WriteContentToFile(const std::string &filePath, const std::string &content, WRITE_MODE placeToWrite){}
std::time_t Filesystem::FileCreationTime(const std::string &filePath){}


std::time_t Filesystem::FileLastModificationTime(const std::string &filePath)
{


#if defined(__linux__) || defined(__unix__)
    if(struct stat fileInfo; stat(filePath.c_str(), &fileInfo) == 0)
    {
        return fileInfo.st_mtime;
    }
#elif defined(__WIN32__) || defined (MSVC)  //maybe for MSVC(compiler not the WIN32's MINGW compiler driver)
    if(struct _stat fileInfo; _stat(filePath.c_str(), &fileInfo) == 0)
    {
        return fileInfo.st_mtime;
    }
#endif

    return -1;
}






//track the file creation time and last file modification time.
//if the last file modification time > creation time then file was modified.
//assign the last modification time to current time(the current time was was checked).

//again if the current modification time > last modification time then file was modified.

bool Filesystem::WasFileModified(const std::string &filePath)
{
    //TODO: we need to also define this for windows and other OS
    if(struct stat fileInfo; stat(filePath.c_str(), &fileInfo) == 0)
    {
        if(fileInfo.st_mtime > lastModificationTime)
        {
            lastModificationTime = fileInfo.st_mtime;
            return true;
        }
    }

    return false;    
}




}
