
#ifndef _PURPURINA_FRWK_API_HPP_
#define _PURPURINA_FRWK_API_HPP_

#include <purpur/core/config/platform.hpp>

////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if defined(_DEBUG) || defined(DEBUG)
	#define PPR_DEBUG
#endif

////////////////////////////////////////////////////////////
// Define import / export macros for each module
////////////////////////////////////////////////////////////
#ifndef PPR_STATIC
	#ifdef PPR_OS_WINDOWS
		#define PPR_API_EXPORT __declspec(dllexport)
		#define PPR_API_IMPORT __declspec(dllimport)
	#else

		#if __GNUC__ >= 4
			// GCC 4 has special keywords for showing/hidding symbols,
			// the same keyword is used for both importing and exporting
			#define PPR_API_EXPORT __attribute__((__visibility__("default")))
			#define PPR_API_IMPORT __attribute__((__visibility__("default")))
		#else
			// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
			#define PPR_API_EXPORT
			#define PPR_API_IMPORT
		#endif

	#endif

#else
	// Static build doesn't need import/export macros
	#define PPR_API_EXPORT
	#define PPR_API_IMPORT
#endif

#endif
