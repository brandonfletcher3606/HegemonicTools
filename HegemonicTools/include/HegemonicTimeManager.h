#pragma once

#include <chrono>
#include <type_traits>

#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
    class HEXPORT_TOOLS TimeManager
    {
    public:
        TimeManager() = default;
        ~TimeManager() = default;

        void setFrequency(std::size_t aFrequency);
        void update();
        bool isPassTime();
        bool updateAndPeek();

        float getDt();
        float getFrequency();

    private:
        using mClock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
        std::chrono::high_resolution_clock,
        std::chrono::steady_clock>;

        mClock::time_point mLastTime = mClock::now();
        float mFrequency = 60;
        // bool mIsPassTime = false;
        double mDt = 0;
        double mRunningDt = 0;
    };
}