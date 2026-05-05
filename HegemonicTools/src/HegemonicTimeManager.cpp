#include "HegemonicTimeManager.h"

namespace Hegemonic
{
    TimeManager::TimeManager() 
    {
        mLastTime = mClock::now();
    }

    void TimeManager::setFrequency(std::size_t aFrequency) 
    { 
        mFrequency = aFrequency; mLastTime = mClock::now();
    };

    void TimeManager::update()
    {
        mClock::time_point currentTime = mClock::now();
        double dt = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - mLastTime).count();
        
        mRunningTime = dt/1000000.0;
    }

    bool TimeManager::isPassTime()
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

    bool TimeManager::updateAndPeek()
    {
        update();
        return isPassTime();;
    }

    float TimeManager::getDt()
    {
        return static_cast<float>(mLastRunningTime);
    }

    float TimeManager::getFrequency()
    {
        return mFrequency;
    }
}