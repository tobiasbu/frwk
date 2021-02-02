////////////////////////////////////////////////////////////
/// Purpurina Engine
///
/// \todo Copyright notice
///
////////////////////////////////////////////////////////////
///
/// \ingroup purpurina_core
/// \file helper_macros.hpp
/// \author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// \date September 14, 2020
///
////////////////////////////////////////////////////////////

#ifndef _PURPURINA_FRWK_HELPER_MACROS_
#define _PURPURINA_FRWK_HELPER_MACROS_

///
/// \brief No Macro
///
#define PPR_NO_MACRO

/////////////////////////////////////////////////
/// \brief Convert macro parameter to string literal.
///
/// \code
/// 	auto a = PPR_STRINGER(3);
/// \endcode
///
/// \param X Value to be stringized
/// \return Stringized value
///
/////////////////////////////////////////////////
#define PPR_STRINGER(X) __PPR_DO_STRINGER(X)
#define __PPR_DO_STRINGER(X) #X

////////////////////////////////////////////////////////////
/// \brief Join two macro arguments together.
///
/// \param X First argument
/// \param Y Second argument
/// \return Joined values
///
////////////////////////////////////////////////////////////
#define PPR_JOIN(X, Y) __PPR_DO_JOIN(X, Y)
#define __PPR_DO_JOIN(X, Y) __PPR_DO_JOIN2(X, Y)
#define __PPR_DO_JOIN2(X, Y) X##Y

#if defined(_MSC_VER)
	#define PPR_ASSERT_ALWAYS_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
	#define PPR_ASSERT_ALWAYS_INLINE inline __attribute__((always_inline))
#else
	#define PPR_ASSERT_ALWAYS_INLINE inline
#endif

#endif
