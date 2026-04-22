#include <cstring>

#include "defines.h"
#include "HegemonicLogger.h"
#include "HegemonicPlatform.h"
#include "HegemonicWindowStructures.h"

#if WINDOWS_PLATFORM

// NOTE: this get included from the windowstructures.h file
//#include <windows.h>
//#include <windowsx.h>

namespace Hegemonic
{
    void platformConsoleWrite(const char* aMessage, int aColor)
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        
        static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };
        SetConsoleTextAttribute(consoleHandle, levels[aColor]);

        OutputDebugStringA(aMessage);
        u64 length = strlen(aMessage);
        LPDWORD numberWritten = 0;
        WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), aMessage, (DWORD)length, numberWritten, 0);
    }

    void platformConsoleWriteError(const char* aMessage, int aColor)
    {
        HANDLE consoleHandle = GetStdHandle(STD_ERROR_HANDLE);

        static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };
        SetConsoleTextAttribute(consoleHandle, levels[aColor]);

        OutputDebugStringA(aMessage);
        u64 length = strlen(aMessage);
        LPDWORD numberWritten = 0;
        WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), aMessage, (DWORD)length, numberWritten, 0);
    }

    void platformSleep(float aDt)
    {
        Sleep(aDt*1000.0f);
    }

    void platformGetExtensionNames(std::vector<const char*>& aExtensions)
    {
        aExtensions.push_back("VK_KHR_win32_surface");
    }

    bool platformIsHandle(void* aWindowState, void* aHandle2)
    {

        WindowInternalState* state = static_cast<WindowInternalState*>(aWindowState);
        HWND handle = static_cast<HWND>(aHandle2);
        return handle == state->hwnd;
    }

    void* platformZeroMememory(void* aMemory, u64 aSize)
    {
        return memset(aMemory, 0, aSize);
    }

    void platformSetCursorPosition(int aX, int aY)
    {
        SetCursorPos(aX, aY);
    }
}

#endif