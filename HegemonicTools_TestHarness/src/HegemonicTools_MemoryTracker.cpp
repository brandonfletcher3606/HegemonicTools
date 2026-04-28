#include <gtest/gtest.h>
#include <HegemonicMemoryTracker.h>

TEST(MemoryTracker, AddTagIsTag)
{
    Hegemonic::MemoryTracker::getInstance().addTag("Test1");
    Hegemonic::MemoryTracker::getInstance().addTag("Test2");
    Hegemonic::MemoryTracker::getInstance().addTag("Test3");

    EXPECT_TRUE(Hegemonic::MemoryTracker::getInstance().isTag("Test1"));
    EXPECT_TRUE(Hegemonic::MemoryTracker::getInstance().isTag("Test2"));
    EXPECT_TRUE(Hegemonic::MemoryTracker::getInstance().isTag("Test3"));
    EXPECT_FALSE(Hegemonic::MemoryTracker::getInstance().isTag("Test4"));
}

TEST(MemoryTracker, IncrimentUp)
{
    Hegemonic::MemoryTracker::getInstance().incrimentUp(10, "Test1");
    EXPECT_TRUE(Hegemonic::MemoryTracker::getInstance().getCount("Test1") == 10);
}

TEST(MemoryTracker, IncrimentDown)
{
    Hegemonic::MemoryTracker::getInstance().incrimentDown(5, "Test1");
    EXPECT_TRUE(Hegemonic::MemoryTracker::getInstance().getCount("Test1") == 5);
}

TEST(MemoryTracker, GetTotal)
{
    Hegemonic::MemoryTracker::getInstance().incrimentUp(10, "Test2");
    Hegemonic::MemoryTracker::getInstance().incrimentUp(20, "Test3");
    EXPECT_TRUE(Hegemonic::MemoryTracker::getInstance().getTotal() == 35);

    Hegemonic::MemoryTracker::getInstance().incrimentDown(5, "Test1");
    Hegemonic::MemoryTracker::getInstance().incrimentDown(10, "Test2");
    Hegemonic::MemoryTracker::getInstance().incrimentDown(20, "Test3");
}