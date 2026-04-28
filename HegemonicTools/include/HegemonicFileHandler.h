#pragma once

#include <string>
#include <vector>

#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
    class HEXPORT FileHandler
    {
    public:
        static bool exists(std::string aFullPath);
        static bool readFile(std::string aFullPath, std::vector<std::string>& aOutData);
        static bool writeFile(std::string aFullPath, std::vector<std::string>& aInData, std::ios_base::openmode aSettings);
        static std::string currentDirectory();
        static std::string buildDirectory(std::initializer_list<std::string> aList);
    };
}