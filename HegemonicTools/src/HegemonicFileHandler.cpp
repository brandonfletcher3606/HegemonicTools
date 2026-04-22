#include <fstream>
#include <iostream>

#include "HegemonicFileHandler.h"

#include <limits.h>
#ifdef WINDOWS_PLATFORM
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

namespace Hegemonic
{
    bool FileHandler::exists(std::string aFullPath)
    {
        std::ifstream inFile(aFullPath);
        return inFile.good();
    }
    bool FileHandler::readFile(std::string aFullPath, std::vector<std::string>& aOutData)
    {
        std::ifstream file(aFullPath);
        std::string line;

        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                aOutData.push_back(line);
            }
            file.close();
        }
        else
        {
            return false;
        }
        return true;
    }
    bool FileHandler::writeFile(std::string aFullPath, std::vector<std::string>& aInData, std::ios_base::openmode aSettings)
    {
        std::ofstream file;
        file.open(aFullPath.c_str(), aSettings);

        if (file.is_open())
        {
            for (int i = 0; i < aInData.size(); i++)
            {
                file << aInData.at(i) << std::endl;;
            }
            file.close();
        }
        else
        {
            return false;
        }
        return true;
    }
    std::string FileHandler::currentDirectory()
    {
        std::string returnString;
        const int PATH_MAX = 100;
        char buff[PATH_MAX];
        if (getcwd(buff, PATH_MAX) != NULL) {
            returnString = std::string(buff);
        }
        return returnString;
    }
    std::string FileHandler::buildDirectory(std::initializer_list<std::string> aList)
    {
        if (aList.size() == 1)
        {
            return *aList.begin();
        }

        if (aList.size() == 0)
        {
            return std::string("");
        }

        std::string returnString;
        for (const auto& str : aList) 
        {
            if (str == *aList.begin())
            {
                returnString += str;
            }
            else
            {
                returnString += std::string(FILESEP) + str;
            }
        }
        returnString += std::string(FILESEP);
        return returnString;
    }
}