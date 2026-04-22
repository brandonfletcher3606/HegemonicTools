#include <gtest/gtest.h>
#include <HegemonicPropertiesHandler.h>
#include <HegemonicFileHandler.h>

#include <HegemonicLogger.h>

TEST(PropertiesHandler, Import)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    EXPECT_TRUE(true);
}

TEST(PropertiesHandler, Clear)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    // load the properties
    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    // take an instance of the Properties
    Hegemonic::Properties p = Hegemonic::PropertiesHandler::getInstance().get();

    // clear the properties
    Hegemonic::PropertiesHandler::getInstance().clear();

    // make sure the properties instance hasn't cleared
    EXPECT_TRUE(p.isProperty("logger.logWarning"));

    // make sure the properties handler has cleared
    EXPECT_FALSE(Hegemonic::PropertiesHandler::getInstance().isProperty("logger.logWarning"));
}

TEST(PropertiesHandler, GetProperty)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    // load the properties
    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    EXPECT_TRUE(std::string("1") == Hegemonic::PropertiesHandler::getInstance().getProperty("logger.logWarning"));
}

TEST(PropertiesHandler, GetPropertyAsDouble)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    // load the properties
    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    EXPECT_TRUE(1.0 == Hegemonic::PropertiesHandler::getInstance().getPropertyAsDouble("logger.logWarning"));
}

TEST(PropertiesHandler, GetPropertyAsFloat)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    // load the properties
    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    EXPECT_TRUE(1.0f == Hegemonic::PropertiesHandler::getInstance().getPropertyAsFloat("logger.logWarning"));
}

TEST(PropertiesHandler, GetPropertyAsInt)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    // load the properties
    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    EXPECT_TRUE(1 == Hegemonic::PropertiesHandler::getInstance().getPropertyAsInt("logger.logWarning"));
}

TEST(PropertiesHandler, GetPropertyAsBool)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    // load the properties
    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    EXPECT_TRUE(Hegemonic::PropertiesHandler::getInstance().getPropertyAsBool("logger.logWarning"));
}

TEST(PropertiesHandler, AddProperty)
{
    std::string directory = Hegemonic::FileHandler::currentDirectory();
    directory = Hegemonic::FileHandler::buildDirectory({directory, "..", "..", "..", "HegemonicTools_TestHarness", "StubData"});

    // load the properties
    Hegemonic::PropertiesHandler::getInstance().loadProperties(directory + std::string("properties.config.txt"));

    // add a property
    Hegemonic::PropertiesHandler::getInstance().addProperty("THIS_IS_A_TEST", "2");

    EXPECT_TRUE(2.0 == Hegemonic::PropertiesHandler::getInstance().getPropertyAsDouble("THIS_IS_A_TEST"));
}
