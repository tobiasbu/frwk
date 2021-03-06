
#ifndef _CHRONOTRIX_FRWK_CONFIG_OS_HPP_
#define _CHRONOTRIX_FRWK_CONFIG_OS_HPP_

////////////////////////////////////////////////////////////
// Set operating system macros
// see
// http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
////////////////////////////////////////////////////////////

#if defined(_WIN32)

	/// Windows
	#define CT_OS_WINDOWS
	/// Windows
	#define CT_OS_WIN32
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif

#elif defined(__APPLE__) && defined(__MACH__)

	// Apple platform, see which one it is
	#include "TargetConditionals.h"

	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

		// iOS
		#define CT_OS_IOS

	#elif TARGET_OS_MAC

		// MacOS
		#define CT_OS_MACOS

	#else

		// Unsupported Apple system
		#error This Apple operating system is not supported by Chronotrix library

	#endif

#elif defined(__unix__)

	// UNIX system, see which one it is
	#if defined(__ANDROID__)

		// Android
		#define CT_OS_ANDROID

	#elif defined(__linux__)

		// Linux
		#define CT_OS_LINUX

	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

		// FreeBSD
		#define CT_OS_FREEBSD

	#else

		// Unsupported UNIX system
		#error This UNIX operating system is not supported by Chronotrix Framework

	#endif

#else

	// Unsupported system
	#error This operating system is not supported by Chronotrix Framework

#endif

#endif
