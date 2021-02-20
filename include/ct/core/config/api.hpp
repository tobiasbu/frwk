
#ifndef _CHRONOTRIX_FRWK_API_HPP_
#define _CHRONOTRIX_FRWK_API_HPP_

#include <ct/core/config/os_detection.hpp>

////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if defined(_DEBUG) || defined(DEBUG)
	#define CT_DEBUG
#endif

////////////////////////////////////////////////////////////
// Define import / export macros for each module
////////////////////////////////////////////////////////////
#ifndef CT_STATIC
	#ifdef CT_OS_WINDOWS
		#define CT_API_EXPORT __declspec(dllexport)
		#define CT_API_IMPORT __declspec(dllimport)
	#else

		#if __GNUC__ >= 4
			// GCC 4 has special keywords for showing/hidding symbols,
			// the same keyword is used for both importing and exporting
			#define CT_API_EXPORT __attribute__((__visibility__("default")))
			#define CT_API_IMPORT __attribute__((__visibility__("default")))
		#else
			// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
			#define CT_API_EXPORT
			#define CT_API_IMPORT
		#endif

	#endif

#else
	// Static build doesn't need import/export macros
	#define CT_API_EXPORT
	#define CT_API_IMPORT
#endif

#endif
