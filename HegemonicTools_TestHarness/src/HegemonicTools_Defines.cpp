#include <gtest/gtest.h>
#include <HegemonicToolsDefines.h>
#include <HegemonicToolsVersion.h>

TEST(Defines, VERSION)
{
    EXPECT_TRUE(Hegemonic::getHegemonicToolsVersion() == "1.0.0");
}