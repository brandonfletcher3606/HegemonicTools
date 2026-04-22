#pragma once

#include <chrono>
#include <type_traits>

#include "defines.h"

namespace Hegemonic
{
    class TimeManager
    {
    public:
        TimeManager() {mLastTime = mClock::now();};
        ~TimeManager() = default;

        void setFrequency(std::size_t aFrequency) { mFrequency = aFrequency; mLastTime = mClock::now();};

        void update()
        {
            mClock::time_point currentTime = mClock::now();
            double dt = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - mLastTime).count();
            
            mRunningTime = dt/1000000.0;
        }

        bool isPassTime()
        {
            bool test = mRunningTime >= (1.0/static_cast<double>(mFrequency)) ? true : false;
            if (test)
            {
                mLastRunningTime = mRunningTime;
                mRunningTime = 0;
                mLastTime = mClock::now();
            }
            return test;
        }

        bool updateAndPeek()
        {
            update();
            return isPassTime();;
        }

        float getDt()
        {
            return static_cast<float>(mLastRunningTime);
        }

    private:
        using mClock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
        std::chrono::high_resolution_clock,
        std::chrono::steady_clock>;

        mClock::time_point mLastTime = mClock::now();
        float mFrequency = 60;
        bool mIsPassTime = false;
        double mRunningTime = 0;
        double mLastRunningTime = 0;
    };
}