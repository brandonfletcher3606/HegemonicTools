#pragma once

#include <chrono>
#include <type_traits>
#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
    class HEXPORT Clock
    {
    public:
        void tic();
        double toc();

    private:
        using mClock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
        std::chrono::high_resolution_clock,
        std::chrono::steady_clock>;

        mClock::time_point mStartTime = mClock::now();
        mClock::time_point mEndTime = mClock::now();
    };
}