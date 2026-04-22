#pragma once

#include <string>

#include "defines.h"

namespace Hegemonic
{
    #if WINDOWS_PLATFORM
        #include <windows.h>
        #include <windowsx.h>
        struct HEXPORT WindowInternalState
        {
            HINSTANCE hinstance;
            HWND hwnd;
        };
    #endif

    struct HEXPORT WindowProperties
    {
        int dimensions[2] = {800, 600};
        int position[2] = {700, 250};
        bool vsync = true;
        std::string title = "Hegemonic Window";
        int id = 0;
    };
}