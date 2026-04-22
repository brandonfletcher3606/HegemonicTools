#include <gtest/gtest.h>
#include <HegemonicFileHandler.h>
#include <HegemonicLogger.h>

TEST(FileHandler, Exists)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});
    EXPECT_TRUE(Hegemonic::FileHandler::exists(directory + std::string("tempExist.txt")));
}

TEST(FileHandler, DoesNotExists)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});
    EXPECT_FALSE(Hegemonic::FileHandler::exists(directory + std::string("tempExistDoesNotExist.txt")));
}

TEST(FileHandler, ReadFile)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});
    std::string file = directory + std::string("tempExist.txt");
    std::vector<std::string> fileData;
    Hegemonic::FileHandler::readFile(file, fileData);

    std::vector<std::string> compareData = {"1", "2", "3", "4", "5"};

    EXPECT_TRUE(fileData.size() == compareData.size());
    if (fileData.size() != compareData.size()) {return;};

    for (int i = 0; i < compareData.size(); i++)
    {
        EXPECT_TRUE(fileData.at(i) == compareData.at(i));
    }
}

TEST(FileHandler, WriteFile)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});
    std::string file = directory + std::string("tempExistOut.txt");
    std::vector<std::string> fileData = {"6", "7", "8", "9", "10"};
    Hegemonic::FileHandler::writeFile(file, fileData, std::ios_base::out);

    std::vector<std::string> compareData;
    Hegemonic::FileHandler::readFile(file, compareData);
    
    EXPECT_TRUE(fileData.size() == compareData.size());
    if (fileData.size() != compareData.size()) {return;};

    for (int i = 0; i < compareData.size(); i++)
    {
        EXPECT_TRUE(fileData.at(i) == compareData.at(i));
    }
}