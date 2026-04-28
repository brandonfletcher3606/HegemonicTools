#include "HegemonicClock.h"

namespace Hegemonic
{
    void Clock::tic() 
    { 
        mStartTime = mClock::now(); 
    };
    double Clock::toc() 
    { 
        mEndTime = mClock::now(); return std::chrono::duration_cast<std::chrono::milliseconds>(mEndTime - mStartTime).count();
    };
}