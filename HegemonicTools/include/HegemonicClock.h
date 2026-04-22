#pragma once

#include <chrono>
#include <type_traits>

namespace Hegemonic
{
    class Clock
    {
    public:
        void tic() { mStartTime = mClock::now(); };
        double toc() { mEndTime = mClock::now(); return std::chrono::duration_cast<std::chrono::milliseconds>(mEndTime - mStartTime).count();};

    private:
        using mClock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
        std::chrono::high_resolution_clock,
        std::chrono::steady_clock>;

        mClock::time_point mStartTime = mClock::now();
        mClock::time_point mEndTime = mClock::now();
    };
}