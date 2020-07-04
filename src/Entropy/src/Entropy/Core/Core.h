#pragma once

#include "Logger.h"

#ifdef _WIN32
	#ifdef _WIN64
	// We're on windows x64
	#define NT_PLATFORM_WINDOWS
	#else
	// We're on windows x86
	#error "x86 not supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	// We're on an Apple device
	#include <TargetConditionals.h>
	#define NT_PLATFORM_APPLE
#elif defined(__ANDROID__)
	#error "Android not supported"
	// We're on Android
#elif defined(__linux__)
	// We're on Linux
	#define NT_PLATFORM_LINUX
#else
	// Unknown platform
	#error "Unknown platform"
#endif

#if defined(NT_PLATFORM_WINDOWS)
	#define NT_DEBUGBREAK() __debugbreak()
#elif defined(NT_PLATFORM_LINUX)
	#include <signal.h>
	#define NT_DEBUGBREAK() raise(SIGTRAP)
#elif defined(NT_PLATFORM_APPLE)
	#define NT_DEBUGBREAK()
#else
	#define NT_DEBUGBREAK()
#endif

#define NT_ASSERT(x, ...) { if(!(x)) { NT_ERROR("Assertion Failed: {0}", __VA_ARGS__); NT_DEBUGBREAK(); } }

#define NT_ATTACH_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)
