#pragma once

#include "HegemonicMemoryTracker.h"
#include "HegemonicPlatform.h"
#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
    template<typename T>
    T* memget(std::string aTag)
    {
        MemoryTracker::getInstance().incrimentUp(sizeof(T), aTag);
        return new T;
    }

    template<typename T, typename... Args>
    T* memget(std::string aTag, Args... aArgs)
    {
        MemoryTracker::getInstance().incrimentUp(sizeof(T), aTag);
        return new T(std::forward<Args>(aArgs)...);
    }

    template<typename T>
    void memgive(T* aMemory, std::string aTag)
    {
        if (aMemory == nullptr)
        {
            return;
        }

        MemoryTracker::getInstance().incrimentDown(sizeof(T), aTag);
        delete aMemory;
    }

    HEXPORT_TOOLS void* memzero(void* aBlock, u64 aSizeOf);
}