
#ifndef _CHRONOTRIX_FRWK_MATH_VEC_HPP_
#define _CHRONOTRIX_FRWK_MATH_VEC_HPP_

#include <ct/config/types.hpp>
#include <ct/math/detail/tvec2.hpp>
#include <ct/math/detail/tvec3.hpp>

namespace ct {

    // TODO(tobiasbu): Currently we don't need specific vectors typedefs
	// Maybe in future?

	// typedef tvec2<i8> vec2c;   ///< Vector2 of 8-bit integer
	// typedef tvec2<u8> vec2uc;  ///< Vector2 of unsigned 8-bit integer
	// typedef tvec2<i16> vec2s;  ///< Vector2 of 16-bit integer
	// typedef tvec2<u16> vec2us; ///< Vector2 of unsigned 16-bit integer
	// typedef tvec2<i64> vec2l;  ///< Vector2 of 64-bit integer
	// typedef tvec2<u64> vec2ul; ///< Vector2 of unsigned 64-bit integer


	// vec2

	typedef tvec2<bool> vec2b; ///< Vector2 of boolean
	typedef tvec2<u32> vec2u;  ///< Vector2 of unsigned 32-bit integer
	typedef tvec2<i32> vec2i;  ///< Vector2 of 32-bit integer
	typedef tvec2<f64> vec2d;  ///< Vector2 of double
	typedef tvec2<f32> vec2;   ///< Vector2 of float

	// vec3

	typedef tvec3<bool> vec3b; ///< Vector3 of boolean
	typedef tvec3<i32> vec3i;  ///< Vector3 of 32-bit integer
	typedef tvec3<u32> vec3u;  ///< Vector3 of unsigned 32-bit integer
	typedef tvec3<f64> vec3d;  ///< Vector3 of double
	typedef tvec3<f32> vec3;   ///< Vector3 of float

}



#endif
