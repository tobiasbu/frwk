
#ifndef _CHRONOTRIX_FRWK_TESTS_MATH_COMMONS_HPP_
#define _CHRONOTRIX_FRWK_TESTS_MATH_COMMONS_HPP_

#include <ct/math/detail/tvec2.hpp>
#include <ct/math/detail/tvec3.hpp>
#include <ct/math/detail/tvec4.hpp>

#include <ct/math/detail/tmat3.hpp>
#include <ct/math/detail/tmat4.hpp>

typedef ct::tvec2<ct::f32> vec2f;
typedef ct::tvec2<ct::i32> vec2i;
typedef ct::tvec2<bool> vec2b;

typedef ct::tvec3<ct::f32> vec3f;
typedef ct::tvec3<ct::i32> vec3i;
typedef ct::tvec3<bool> vec3b;

typedef ct::tvec4<ct::f32> vec4f;
typedef ct::tvec4<ct::i32> vec4i;
typedef ct::tvec4<bool> vec4b;

typedef ct::tmat3<ct::f32> mat3;
typedef ct::tmat3<ct::f64> mat3d;

typedef ct::tmat4<ct::f32> mat4;
typedef ct::tmat4<ct::f64> mat4d;


constexpr float max(float a, float b) {
	return a > b ? a : b;
}

constexpr float EPSILON = 0.0001f;

bool essentially_equal(float a, float b, float epsilon = EPSILON) {
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
bool approximately_equal(float a, float b, float epsilon = EPSILON) {
	return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool approximately_equal(vec3f a, vec3f b, float epsilon = EPSILON) {
	return approximately_equal(a.x, b.x) &&
		   approximately_equal(a.y, b.y) &&
	       approximately_equal(a.z, b.z);
}
bool approximately_equal(vec4f a, vec4f b, float epsilon = EPSILON) {
	return approximately_equal(a.x, b.x) &&
		   approximately_equal(a.y, b.y) &&
	       approximately_equal(a.z, b.z) &&
	       approximately_equal(a.w, b.w);
}



bool approximately_equals(const mat4 & a, const mat4 & b, float epsilon = 0.0001) {
	for (int i = 0; i < 4; i += 1) {
		if (!approximately_equal(a.col(i), b.col(i))) {
			return false;
		}
	}
	return true;
}


#endif
