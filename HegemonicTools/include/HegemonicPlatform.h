
#pragma once

#include <vector>

#include "defines.h"

namespace Hegemonic
{
    HEXPORT void platformConsoleWrite(const char* aMessage, int aColor);
    HEXPORT void platformConsoleWriteError(const char* aMessage, int aColor);  
    HEXPORT void platformSleep(float aDt);
    HEXPORT void platformGetExtensionNames(std::vector<const char*>& aExtensions);
    HEXPORT bool platformIsHandle(void* aWindowState, void* aHandle2);
    HEXPORT void* platformZeroMememory(void* aMemory, u64 aSize);
    HEXPORT void platformSetCursorPosition(int aX, int aY);
}