
#ifndef _CHRONOTRIX_FRWK_TESTS_MATH_HPP_
#define _CHRONOTRIX_FRWK_TESTS_MATH_HPP_

#include <ct/math/detail/tvec2.hpp>
#include <ct/math/detail/tvec3.hpp>

typedef ct::tvec2<ct::f32> vec2f;
typedef ct::tvec2<ct::i32> vec2i;
typedef ct::tvec2<bool> vec2b;

typedef ct::tvec3<ct::f32> vec3f;
typedef ct::tvec3<ct::i32> vec3i;
typedef ct::tvec3<bool> vec3b;


constexpr float max(float a, float b) {
	return a > b ? a : b;
}

constexpr float epsilon = 0.0001f;
bool approximatelyEqual(float a, float b) {
	return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
bool essentiallyEqual(float a, float b) {
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}


#endif
