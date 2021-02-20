
#ifndef _CHRONOTRIX_FRWK_BREAKPOINT_HPP_
#define _CHRONOTRIX_FRWK_BREAKPOINT_HPP_

#include <ct/core/config/api.hpp>

#ifdef CT_DEBUG
	#if defined(_MSC_VER)
		extern void __cdecl __debugbreak(void);
		#define CT_BREAKPOINT() __debugbreak()
	#else
		#if defined(__APPLE__)
			#include <TargetConditionals.h>
		#endif

		#if defined(__clang__) && !TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
			#define CT_BREAKPOINT() __builtin_debugtrap()

		#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__APPLE__)
			#include <signal.h>
			#define CT_BREAKPOINT() raise(SIGTRAP)

		#elif defined(__GNUC__)
			#define CT_BREAKPOINT() __builtin_trap()

		#else
			#define CT_BREAKPOINT() ((void)0)
			#error "Platform doesn't support debugbreak!"
		#endif
	#endif
#else
	#define CT_BREAKPOINT()
#endif

#endif
