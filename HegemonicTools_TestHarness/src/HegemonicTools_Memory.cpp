#include <gtest/gtest.h>
#include <HegemonicMemory.h>
#include <HegemonicLogger.h>

TEST(Memory, MEMZERO)
{
    int a = 42;
    Hegemonic::memzero(&a, sizeof(int));
    EXPECT_TRUE(a == 0);
}

TEST(Memory, MEMGETTAG)
{
    Hegemonic::MemoryTracker::getInstance().addTag("TEST");

    int *a = Hegemonic::memget<int>("TEST");
    Hegemonic::memzero(a, sizeof(int));
    EXPECT_TRUE(*a == 0);

    Hegemonic::memgive(a, "TEST");

    auto res = [](int x) {
        return x + x;
    };
}

TEST(Memory, MEMGETFUNCTION)
{
    struct TestStruct
    {
        TestStruct(int a, double b) : a(a), b(b) {};
        int a = 0;
        double b = 0.0;
    };

    TestStruct* t = Hegemonic::memget<TestStruct>("TEST", 5, 6.2);

    EXPECT_TRUE(t->a == 5);
    EXPECT_TRUE(t->b == 6.2);

    Hegemonic::memgive(t, "TEST");
}