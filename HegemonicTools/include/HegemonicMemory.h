#pragma once

#include "HegemonicMemoryTracker.h"
#include "HegemonicPlatform.h"
#include "HegemonicToolsDefines.h"

#include <utility>

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

    template<typename T, typename... Args>
    std::unique_ptr<T> makeUnique(Args &&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<typename T, typename... Args>
    std::unique_ptr<T> makeUnique(std::string aTag, Args &&... args)
    {
        return std::unique_ptr<T>(memget<T, Args>(aTag));
    }

    HEXPORT_TOOLS void* memzero(void* aBlock, u64 aSizeOf);
}