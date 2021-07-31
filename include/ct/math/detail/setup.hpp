
#ifndef _CHRONOTRIX_FRWK_MATH_SETUP_HPP_
#define _CHRONOTRIX_FRWK_MATH_SETUP_HPP_

#include <ct/config.hpp>

#if defined(CT_ASSERT)
	#define __CT_MATH_ASSERT CT_ASSERT
#elif defined(assert)
	#define __CT_MATH_ASSERT assert
#else
	#define __CT_MATH_ASSERT(...) (void)0
#endif

#define CT_MATH_FUNC CT_CONSTEXPR
#define CT_MATH_FUNC_INL CT_FORCE_INLINE CT_CONSTEXPR

namespace ct {

	template <typename T>
	struct tvec2;
	template <typename T>
	struct tvec3;
	template <typename T>
	struct tvec4;

	template <typename T>
	struct tmat3;
	template <typename T>
	struct tmat4;

	template <typename T>
	struct trect;

} // namespace ct

#endif
