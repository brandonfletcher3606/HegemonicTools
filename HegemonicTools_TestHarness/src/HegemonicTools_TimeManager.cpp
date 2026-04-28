#include <gtest/gtest.h>
#include <HegemonicTimeManager.h>
#include <HegemonicLogger.h>

#include <thread>

TEST(TimeManager, GetFrequency)
{
    Hegemonic::TimeManager tm = Hegemonic::TimeManager();
    tm.setFrequency(100);
    EXPECT_TRUE(tm.getFrequency() == 100);
}

TEST(TimeManager, Update)
{
    using namespace std::chrono_literals;
    
    Hegemonic::setLoggingPrecision(15);
    Hegemonic::TimeManager tm = Hegemonic::TimeManager();
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(10ms);
        tm.update();
        double dt = tm.getDt();
        EXPECT_TRUE(dt < 0.02);
    }
}

TEST(TimeManager, UpdateAndPeek)
{
    // this test is not very robust, mya need to add a Hegemonic::Clock to evaluate with tic and toc
    // evaluating at 10ms but it appears to take 15ms (some overhead) at 60 hz every other update and Peek will trigger
    // If this runs on a different processor, it could mess it up
    using namespace std::chrono_literals;
    
    Hegemonic::setLoggingPrecision(15);
    Hegemonic::TimeManager tm = Hegemonic::TimeManager();
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(10ms);
        bool testBool = tm.updateAndPeek();
        if (i % 2)
        {
            EXPECT_TRUE(testBool);
        }
        else
        {
            EXPECT_FALSE(testBool);
        }
    }
}