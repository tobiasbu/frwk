////////////////////////////////////////////////////////////
/// Purpurina Engine
///
/// \todo Copyright notice
///
////////////////////////////////////////////////////////////
///
/// \ingroup purpurina-core
/// \file Config.hpp
/// \author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// \date March 7, 2020
///
////////////////////////////////////////////////////////////

#ifndef _PURPURINA_CONFIG_HPP_
#define _PURPURINA_CONFIG_HPP_

	////////////////////////////////////////////////////////////
	// Purpurina version
	////////////////////////////////////////////////////////////
	#define PURPURINA_VERSION_MAJOR 0
	#define PURPURINA_VERSION_MINOR 0
	#define PURPURINA_VERSION_PATCH 1

	////////////////////////////////////////////////////////////
	// Set operating system
	// see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
	////////////////////////////////////////////////////////////
	#if defined(_WIN32)

		/// Windows OS
		#define PPR_OS_WINDOWS
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif

	#elif defined(__APPLE__) && defined(__MACH__)

		// Apple platform, see which one it is
		#include "TargetConditionals.h"

		#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

		// iOS
		#define PPR_OS_IOS

		#elif TARGET_OS_MAC

		// MacOS
		#define PPR_OS_MACOS

		#else

		// Unsupported Apple system
		#error This Apple operating system is not supported by Purpurina library

		#endif

	#elif defined(__unix__)

		// UNIX system, see which one it is
		#if defined(__ANDROID__)

			// Android
			#define PPR_OS_ANDROID

		#elif defined(__linux__)

			// Linux
			#define PPR_OS_LINUX

		#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

			// FreeBSD
			#define PPR_OS_FREEBSD

		#else

			// Unsupported UNIX system
			#error This UNIX operating system is not supported by Purpurina engine

		#endif

	#else

		// Unsupported system
		#error This operating system is not supported by Purpurina engine

	#endif

	////////////////////////////////////////////////////////////
	// Define a portable debug macro
	////////////////////////////////////////////////////////////
	#if !defined(NDEBUG)
		#define PPR_DEBUG
	#endif

	////////////////////////////////////////////////////////////
	// Define import / export macros for each module
	////////////////////////////////////////////////////////////
	#ifndef PURPURINA_STATIC
		#ifdef PPR_OS_WINDOWS
			#define PURPURINA_API_EXPORT __declspec(dllexport)
        	#define PURPURINA_API_IMPORT __declspec(dllimport)
		#else

			#if __GNUC__ >= 4
				// GCC 4 has special keywords for showing/hidding symbols,
				// the same keyword is used for both importing and exporting
				#define PURPURINA_API_EXPORT __attribute__ ((__visibility__ ("default")))
				#define PURPURINA_API_IMPORT __attribute__ ((__visibility__ ("default")))
			#else
				// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
				#define PURPURINA_API_EXPORT
				#define PURPURINA_API_IMPORT
			#endif

		#endif

	#else
		// Static build doesn't need import/export macros
		#define PURPURINA_API_EXPORT
		#define PURPURINA_API_IMPORT
	#endif

	#if (defined (__cplusplus) && (__cplusplus > 199711L)) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 150020706))
		#define PURPURINA_CXX11
	#endif

	#if defined(PURPURINA_CXX11)
		// Null pointer
		#define PPR_NULLPTR nullptr
	#else
		// Null pointer
		#define PPR_NULLPTR 0
	#endif


///
/// Purpurina namespace
///
namespace ppr
{
	////////////////////////////////////////////////////////////
	// Define portable fixed-size types
	////////////////////////////////////////////////////////////

	// All "common" platforms use the same size for char, short and int
	// (basically there are 3 types for 3 sizes, so no other match is possible),
	// we can use them without doing any kind of check

	/// C-string
	typedef const char * cstr;

	// 8 bits integer types
	typedef signed   char int8;
	typedef unsigned char uint8;

	// 16 bits integer types
	typedef signed   short int16;
	typedef unsigned short uint16;

	// 32 bits integer types
	typedef signed   int int32;
	typedef unsigned int uint32;

	// 64 bits integer types
	#if defined(_MSC_VER)
		typedef signed   __int64 int64;
		typedef unsigned __int64 uint64;
	#else
		typedef signed   long long int64;
		typedef unsigned long long uint64;
	#endif
} // namespace ppr

#endif



