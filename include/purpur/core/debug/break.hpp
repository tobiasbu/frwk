

#ifndef _PURPURINA_DEBUG_BREAK_HPP_
#define _PURPURINA_DEBUG_BREAK_HPP_

#include <purpur/core/config.hpp>

#ifdef PPR_DEBUG
	#if defined(PPR_OS_WINDOWS)
		extern void __cdecl __debugbreak(void);
		#define PPR_DEBUGBREAK() __debugbreak()
	#else
		#if defined(__APPLE__)
			#include <TargetConditionals.h>
		#endif

		#if defined(__clang__) && !TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
			#define PPR_DEBUGBREAK() __builtin_debugtrap()

		#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__APPLE__)
			#include <signal.h>
			#define PPR_DEBUGBREAK() raise(SIGTRAP)

		#elif defined(__GNUC__)
			#define PPR_DEBUGBREAK() __builtin_trap()

		#else
			#define PPR_DEBUGBREAK() ((void)0)
			#error "Platform doesn't support debugbreak!"
		#endif
	#endif
#else
	#define PPR_DEBUGBREAK()
#endif

#endif
