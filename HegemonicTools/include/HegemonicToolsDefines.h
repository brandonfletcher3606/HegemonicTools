#pragma once

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	// Windows logic
	#define WINDOWS_PLATFORM 1
	#define LINUX_PLATFORM 0
	#define FILESEP "\\"
    #ifdef BUILDING_HEGEMONIC_TOOLS
        #define HEXPORT __declspec(dllexport)
    #else
        #define HEXPORT __declspec(dllimport)
    #endif
#else
    // Linux/Unix logic
	#define WINDOWS_PLATFORM 0
	#define LINUX_PLATFORM 1
	#define FILESEP "/"
    #if __GNUC__ >= 4
        #define HEXPORT __attribute__((visibility("default")))
    #else
        #define HEXPORT
    #endif
#endif

namespace Hegemonic
{
	// unsigned int types
	typedef unsigned char u8;
	typedef unsigned short u16;
	typedef unsigned int u32;
	typedef unsigned long long u64;

	// signed int types
	typedef signed char i8;
	typedef signed short i16;
	typedef signed int i32;
	typedef signed long long i64;

	// floating point types
	typedef float f32;
	typedef double f64;

	// boolean types
	typedef int b32;
	typedef char b8;

	HEXPORT std::string getHegemonicToolsVersion();
}

#define INVALIDID 4294967295U

