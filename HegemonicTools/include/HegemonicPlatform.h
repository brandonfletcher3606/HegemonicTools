
#pragma once

#include <vector>

#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
    HEXPORT_TOOLS void platformConsoleWrite(const char* aMessage, int aColor);
    HEXPORT_TOOLS void platformConsoleWriteError(const char* aMessage, int aColor);  
    HEXPORT_TOOLS void platformSleep(float aDt);
    HEXPORT_TOOLS void platformGetExtensionNames(std::vector<const char*>& aExtensions);
    HEXPORT_TOOLS bool platformIsHandle(void* aWindowState, void* aHandle2);
    HEXPORT_TOOLS void* platformZeroMememory(void* aMemory, u64 aSize);
    HEXPORT_TOOLS void platformSetCursorPosition(int aX, int aY);
}