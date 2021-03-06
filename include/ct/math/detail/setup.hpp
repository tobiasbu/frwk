
#ifndef _CHRONOTRIX_FRWK_MATH_SETUP_HPP_
#define _CHRONOTRIX_FRWK_MATH_SETUP_HPP_

#include <ct/config.hpp>

#if defined(CT_ASSERT)
	#define __CT_MATH_ASSERT CT_ASSERT
#elif defined(assert)
	#define __CT_MATH_ASSERT assert
#else
	#define __CT_MATH_ASSERT(...) ((0)void)
#endif

namespace ct {

	template <typename T>
	struct vec2;
	template <typename T>
	struct vec3;
	template <typename T>
	struct vec4;

	template <typename T>
	struct mat3;
	template <typename T>
	struct mat4;

} // namespace ct

#endif
