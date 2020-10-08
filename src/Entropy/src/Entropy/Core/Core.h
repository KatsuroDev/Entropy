#pragma once

#include "Logger.h"

#include <stdlib.h>
#include <string.h>
#include <memory>

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
// We're on Android
#error "Android not supported"
#elif defined(__linux__)
// We're on Linux
#define NT_PLATFORM_LINUX
#else
// Unknown platform
#error "Unknown platform (not supported)"
#endif


#if defined(NT_PLATFORM_WINDOWS)
#define NT_DEBUGBREAK() __debugbreak()
#elif defined(NT_PLATFORM_LINUX)
#include <signal.h>
#define NT_DEBUGBREAK() raise(SIGTRAP)
#elif defined(NT_PLATFORM_APPLE)
#define NT_DEBUGBREAK() abort()
#else
#define NT_DEBUGBREAK()
#endif


#define NT_FATAL(...) { NT_ERROR(__VA_ARGS__); NT_DEBUGBREAK(); }

#define NT_ASSERT(x, ...) { if(!(x)) { NT_ERROR(__VA_ARGS__); NT_DEBUGBREAK(); } }

#define NT_ATTACH_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)


namespace Entropy {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
