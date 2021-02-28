////////////////////////////////////////////////////////////
// Chronotrix Framework
//
// @todo Copyright notice
//
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_HELPER_MACROS_
#define _CHRONOTRIX_FRWK_HELPER_MACROS_

///
/// @brief No Macro
///
#define CT_NO_MACRO

/////////////////////////////////////////////////
/// @brief Convert macro parameter to string literal.
///
/// @code
/// 	auto a = CT_STRINGER(3);
/// @endcode
///
/// @param X Value to be stringized
/// @return Stringized value
///
/////////////////////////////////////////////////
#define CT_STRINGER(X) __CT_DO_STRINGER(X)
#define __CT_DO_STRINGER(X) #X

////////////////////////////////////////////////////////////
/// @brief Join two macro arguments together.
///
/// @param X First argument
/// @param Y Second argument
/// @return Joined values
///
////////////////////////////////////////////////////////////
#define CT_JOIN(X, Y) __CT_DO_JOIN(X, Y)
#define __CT_DO_JOIN(X, Y) __CT_DO_JOIN2(X, Y)
#define __CT_DO_JOIN2(X, Y) X##Y

#if defined(_MSC_VER)
	#define CT_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
	#define CT_FORCE_INLINE inline __attribute__((always_inline))
#else
	#define CT_FORCE_INLINE inline
#endif

#endif

////////////////////////////////////////////////////////////
/// @file helper_macros.hpp
/// @ingroup core
/// @author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// @date September 14, 2020
///
////////////////////////////////////////////////////////////
