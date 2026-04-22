#pragma once

#include "HegemonicMemoryTracker.h"
#include "HegemonicPlatform.h"

namespace Hegemonic
{
    template<typename T>
    T* memget(MemoryTag aTag)
    {
        MemoryTracker::getInstance().incrimentUp(sizeof(T), aTag);
        return new T;
    }

    template<typename T, typename... Args>
    T* memget(MemoryTag aTag, Args... aArgs)
    {
        MemoryTracker::getInstance().incrimentUp(sizeof(T), aTag);
        return new T(std::forward<Args>(aArgs)...);
    }

    template<typename T>
    void memgive(T* aMemory, MemoryTag aTag)
    {
        if (aMemory == nullptr)
        {
            return;
        }

        MemoryTracker::getInstance().incrimentDown(sizeof(T), aTag);
        delete aMemory;
    }

    void* memzero(void* aBlock, u64 aSizeOf);
}