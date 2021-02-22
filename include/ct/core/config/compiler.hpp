
#ifndef _CHRONOTRIX_FRWK_COMPILER_FEATURES_HPP_
#define _CHRONOTRIX_FRWK_COMPILER_FEATURES_HPP_

#if defined(__cplusplus)
	#if (__cplusplus > 199711L) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 150020706))
		#define CT_CXX11
	#endif

	#if __cplusplus >= 201402L
		#define CT_CXX14
	#endif

	#if __cplusplus >= 201703L
		#define CT_CXX17
	#endif

#endif

#if defined __clang__ && !defined(__ibmxl__) && !defined(__CODEGEARC__)
	#include <ct/core/config/compiler/clang.hpp>
#elif defined(__GNUC__) && !defined(__ibmxl__)
	#include <ct/core/config/compiler/gcc.hpp>
#elif defined(_MSC_VER)
	#include <ct/core/config/compiler/msvc.hpp>
#endif

////////////////////////////////////////////////////////////
// Define NULLPTR macro
////////////////////////////////////////////////////////////
#ifdef CT_CXX11
	/// Null pointer
	#define NULLPTR nullptr
#else
	/// Null pointer
	#define NULLPTR 0
#endif

////////////////////////////////////////////////////////////
// Define CONSTEXPR macro
////////////////////////////////////////////////////////////
#ifdef CT_CXX11_HAS_CONSTEXPR
	#define CONSTEXPR constexpr
#else
	#define CONSTEXPR
#endif

////////////////////////////////////////////////////////////
// Define NOEXCEPT macro
////////////////////////////////////////////////////////////
#ifdef CT_CXX11_HAS_NOEXCEPT
	/// noexcept
	#define NOEXCEPT noexcept
#else
	/// noexcept
	#define NOEXCEPT
#endif

////////////////////////////////////////////////////////////
// Define NODISCARD macro
////////////////////////////////////////////////////////////
#ifndef CT_HAS_NODISCARD
	#ifndef __has_cpp_attribute
		#define CT_HAS_NODISCARD 0
	#elif __has_cpp_attribute(nodiscard) >= 201603L
		#define CT_HAS_NODISCARD 1
	#else
		#define CT_HAS_NODISCARD 0
	#endif
#endif

#if CT_HAS_NODISCARD
	#define NODISCARD [[nodiscard]]
#else
	#define NODISCARD
#endif


#endif
