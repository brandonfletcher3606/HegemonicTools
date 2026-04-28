#include <gtest/gtest.h>
#include <HegemonicToolsDefines.h>

TEST(Defines, VERSION)
{
    EXPECT_TRUE(Hegemonic::getHegemonicToolsVersion() == "1.0.0");
}