#include "HegemonicMemory.h"
#include "HegemonicLogger.h"

namespace Hegemonic
{
    void* memzero(void* aBlock, u64 aSizeOf)
    {
        if (!aBlock)
        {
            Hegemonic::logFatal("memzero block memory cannot be a nullptr or empty");
        }
        return Hegemonic::platformZeroMememory(aBlock, aSizeOf);
    };
}