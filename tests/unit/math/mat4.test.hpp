
#include <doctest.h>
#include <iostream>

#include "../../commons/math_commons.hpp"


TEST_CASE("math/mat4") {
	SUBCASE("determinant") {
		mat4 a(1, 4, 1, 5,
			3, 7, 9, 8,
			7, 11, 12, 13,
			10, 6, 4, 9);
		CHECK(a.determinant() == 87.f);
		a.set(1, 10, 20, 30, 2, 11, 21, 31, 3, 31, 32, 34, 4, 41, 42, 44);
		CHECK(a.determinant() == -90.f);
		a.set(4, -2, 2, 1, 2, 4, 3, 1, 3, 7, 11, 2, 9, -7, 1, 0);
		CHECK(a.determinant() == -224.f);
	}
}
