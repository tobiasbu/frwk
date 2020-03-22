
#ifndef _PURPURINA_CONFIG_HPP_
#define _PURPURINA_CONFIG_HPP_

	////////////////////////////////////////////////////////////
	// PURPURINA CORE version
	////////////////////////////////////////////////////////////
	#define PURPURINA_VERSION_MAJOR 0
	#define PURPURINA_VERSION_MINOR 0
	#define PURPURINA_VERSION_PATCH 1

	////////////////////////////////////////////////////////////
	// Set operating system
	// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
	////////////////////////////////////////////////////////////
	#if defined(_WIN32)

		// Windows
		#define PURPURINA_OS_WINDOWS
			#ifndef NOMINMAX
				#define NOMINMAX
			#endif

	#elif defined(__APPLE__) && defined(__MACH__)

		// Apple platform, see which one it is
		// #include "TargetConditionals.h"

		#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

		// iOS
		#define PURPURINA_OS_IOS

		#elif TARGET_OS_MAC

		// MacOS
		#define PURPURINA_OS_MACOS

		#else

		// Unsupported Apple system
		#error This Apple operating system is not supported by KING library

		#endif

	#elif defined(__unix__)

		// UNIX system, see which one it is
		#if defined(__ANDROID__)

		// Android
		#define PURPURINA_OS_ANDROID

		#elif defined(__linux__)

		// Linux
		#define PURPURINA_OS_LINUX

		#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

		// FreeBSD
		#define PURPURINA_OS_FREEBSD

		#else

		// Unsupported UNIX system
		#error This UNIX operating system is not supported by KING library

		#endif

	#else

		// Unsupported system
		#error This operating system is not supported by KING library

	#endif

	////////////////////////////////////////////////////////////
	// Define a portable debug macro
	////////////////////////////////////////////////////////////
	#if !defined(NDEBUG)

		#define PURPURINA_DEBUG

	#endif

#endif
