#include <gtest/gtest.h>
#include <HegemonicClock.h>
#include <HegemonicLogger.h>

#include <thread>

TEST(Clock, TicToc)
{
    Hegemonic::Clock c = Hegemonic::Clock();
    c.tic();

    // Use standard chrono literals for readability (requires 'using namespace std::chrono_literals')
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);

    double b = c.toc();

    EXPECT_TRUE(b < 120);
}