#include "HegemonicMemory.h"

namespace Hegemonic
{
    void* memzero(void* aBlock, u64 aSizeOf)
    {
        return Hegemonic::platformZeroMememory(aBlock, aSizeOf);
    };
}