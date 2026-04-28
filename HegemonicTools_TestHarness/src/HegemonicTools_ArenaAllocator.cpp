#include <gtest/gtest.h>
#include <HegemonicArenaAllocator.h>

TEST(ArenaAllocator, AllocateNotFull)
{
    Hegemonic::ArenaAllocator<1024>* arena = new Hegemonic::ArenaAllocator<1024>();

    struct TestStruct
    {
        TestStruct(int a, double b) : a(a), b(b) {};
        TestStruct() {};
        int a = 1;
        double b = 2.0;
    };

    TestStruct *a = arena->allocate<TestStruct>();
    EXPECT_TRUE(a->a == 1);
    EXPECT_TRUE(a->b == 2.0);
    EXPECT_TRUE(arena->isUsed() == sizeof(TestStruct));

    delete arena;
}

TEST(ArenaAllocator, AllocateNotFullMultiple)
{
    Hegemonic::ArenaAllocator<1024>* arena = new Hegemonic::ArenaAllocator<1024>();

    struct TestStruct
    {
        TestStruct(int a, double b) : a(a), b(b) {};
        TestStruct() {};
        int a = 1;
        double b = 2.0;
    };

    TestStruct *a = arena->allocate<TestStruct>();
    EXPECT_TRUE(a->a == 1);
    EXPECT_TRUE(a->b == 2.0);
    EXPECT_TRUE(arena->isUsed() == sizeof(TestStruct));

    TestStruct *b = arena->allocate<TestStruct>();
    EXPECT_TRUE(b->a == 1);
    EXPECT_TRUE(b->b == 2.0);
    EXPECT_TRUE(arena->isUsed() == 2*sizeof(TestStruct));

    delete arena;
}

TEST(ArenaAllocator, AllocateFullThrow)
{
    struct TestStruct
    {
        TestStruct(int a, double b) : a(a), b(b) {};
        TestStruct() {};
        int a = 1;
        double b = 2.0;
    };

    const size_t s = sizeof(TestStruct);
    Hegemonic::ArenaAllocator<s>* arena = new Hegemonic::ArenaAllocator<s>();

    TestStruct *a = arena->allocate<TestStruct>();
    EXPECT_TRUE(a->a == 1);
    EXPECT_TRUE(a->b == 2.0);
    EXPECT_TRUE(arena->isUsed() == sizeof(TestStruct));

    EXPECT_THROW(arena->allocate<TestStruct>(), std::bad_alloc);

    delete arena;
}

TEST(ArenaAllocator, IsAvailable)
{
    struct TestStruct
    {
        TestStruct(int a, double b) : a(a), b(b) {};
        TestStruct() {};
        int a = 1;
        double b = 2.0;
    };

    const size_t s = 2*sizeof(TestStruct);
    Hegemonic::ArenaAllocator<s>* arena = new Hegemonic::ArenaAllocator<s>();

    TestStruct *a = arena->allocate<TestStruct>();
    EXPECT_TRUE(arena->isAvailable() == sizeof(TestStruct));

    delete arena;
}

TEST(ArenaAllocator, Get)
{
    Hegemonic::ArenaAllocator<1024>* arena = new Hegemonic::ArenaAllocator<1024>();

    void* buffer = arena->get();
    EXPECT_TRUE(_msize(buffer) == 1024);

    delete arena;
}