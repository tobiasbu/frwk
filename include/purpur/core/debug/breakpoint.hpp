

#ifndef _PURPURINA_FRWK_BREAKPOINT_HPP_
#define _PURPURINA_FRWK_BREAKPOINT_HPP_

#include <purpur/core/config/platform.hpp>

#ifdef PPR_DEBUG
	#if defined(_MSC_VER)
		extern void __cdecl __debugbreak(void);
		#define PPR_BREAKPOINT() __debugbreak()
	#else
		#if defined(__APPLE__)
			#include <TargetConditionals.h>
		#endif

		#if defined(__clang__) && !TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
			#define PPR_BREAKPOINT() __builtin_debugtrap()

		#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__APPLE__)
			#include <signal.h>
			#define PPR_BREAKPOINT() raise(SIGTRAP)

		#elif defined(__GNUC__)
			#define PPR_BREAKPOINT() __builtin_trap()

		#else
			#define PPR_BREAKPOINT() ((void)0)
			#error "Platform doesn't support debugbreak!"
		#endif
	#endif
#else
	#define PPR_BREAKPOINT()
#endif

#endif
