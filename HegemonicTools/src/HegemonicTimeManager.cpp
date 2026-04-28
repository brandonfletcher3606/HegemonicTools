#include "HegemonicTimeManager.h"

namespace Hegemonic
{
    void TimeManager::setFrequency(std::size_t aFrequency) 
    { 
        mFrequency = aFrequency; 
        mLastTime = mClock::now();
    };

    void TimeManager::update()
    {
        // get dt from last time
        // set the running dt
        // update last time to current time
        mClock::time_point currentTime = mClock::now();
        double dt = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - mLastTime).count();
        
        mDt = dt/1000000.0;
        mLastTime = currentTime;
        mRunningDt += mDt;
    }
    bool TimeManager::isPassTime()
    {
        bool test = mRunningDt >= (1.0/static_cast<double>(mFrequency)) ? true : false;
        if (test)
        {
            mRunningDt = 0;
            mDt = 0;
        }
        return test;
    }
    bool TimeManager::updateAndPeek()
    {
        update();
        return isPassTime();
    }

    float TimeManager::getDt()
    {
        return static_cast<float>(mDt);
    }
    float TimeManager::getFrequency()
    {
        return mFrequency;
    }
}