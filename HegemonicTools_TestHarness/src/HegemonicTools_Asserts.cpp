#include <gtest/gtest.h>
#include <HegemonicAsserts.h>

TEST(Asserts, HASSERTBool)
{
    int a = 5;
    HASSERT(a == 5);
}

TEST(Asserts, HASSERTBoolMessage)
{
    int a = 5;
    HASSERT_MSG(a == 5, "This is a test");
}