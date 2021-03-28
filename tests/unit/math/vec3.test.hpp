#include <doctest.h>
#include "commons.hpp"

TEST_CASE("math/vec3") {

	SUBCASE("default constructors") {
		vec3f def_zero;
		CHECK(def_zero.x == 0.f);
		CHECK(def_zero.y == 0.f);
		CHECK(def_zero.z == 0.f);

		vec3f copy_src(14.78f, 56.3467f, -42.0f);
		vec3f copy_dest(copy_src);
		CHECK(copy_dest.x == 14.78f);
		CHECK(copy_dest.y == 56.3467f);
		CHECK(copy_dest.z == -42.0f);
	}

	SUBCASE("explicit constructors") {
		vec3f expl_vec(42.f,13.f,196.f);
		CHECK(expl_vec.x == 42.f);
		CHECK(expl_vec.y == 13.f);
		CHECK(expl_vec.z == 196.f);

		vec3f expl_scalar(84.f);
		CHECK(expl_scalar.x == 84.f);
		CHECK(expl_scalar.y == 84.f);
		CHECK(expl_scalar.z == 84.f);
	}

	SUBCASE("conversion constructors") {
		vec3f convert_from_uint(8u, 9u, 17u);
		CHECK(convert_from_uint.x == 8.f);
		CHECK(convert_from_uint.y == 9.f);
		CHECK(convert_from_uint.z == 17.f);

		vec3i i32_vec(1024, 800, -64);
		vec3f f32_vec(i32_vec);
		CHECK(f32_vec.x == 1024.f);
		CHECK(f32_vec.y == 800.f);
		CHECK(f32_vec.z == -64.f);
	}

	SUBCASE("conversion constructors - from vec2") {
		vec2f v2(-47.f, 2.f);
		vec3f from_vec2(v2, 14.f);
		CHECK(from_vec2.x == -47.f);
		CHECK(from_vec2.y == 2.f);
		CHECK(from_vec2.z == 14.f);

		vec2f v2_1(-98.f, 253.f);
		vec3f from_vec2_1(v2_1);
		CHECK(from_vec2_1.x == -98.f);
		CHECK(from_vec2_1.y == 253.f);
		CHECK(from_vec2_1.z == 0.f);

		vec2f v2_2(2.589f, 3.5f);
		vec3i from_vec2_2(v2_2);
		CHECK(from_vec2_2.x == 2);
		CHECK(from_vec2_2.y == 3);
		CHECK(from_vec2_2.z == 0);

		vec2f v2_3(0.12459f, -5464.8f);
		vec3i from_vec2_3(v2_3, 47.f);
		CHECK(from_vec2_3.x == 0);
		CHECK(from_vec2_3.y == -5464);
		CHECK(from_vec2_3.z == 47);
	}

	SUBCASE("assign operators: =") {
		vec3i assign_src(1400.45f,900, 896);
		auto assign_dst = assign_src;
		CHECK(assign_dst.x == 1400);
		CHECK(assign_dst.y == 900);
		CHECK(assign_dst.z == 896);

		vec3f assign_convert_src(150.893245f,1984.123459f, 4.23455f);
		vec3i assign_convert_dst = assign_convert_src;
		CHECK(assign_convert_dst.x == 150);
		CHECK(assign_convert_dst.y == 1984);
		CHECK(assign_convert_dst.z == 4);
	}

	SUBCASE("unary operators: +=") {
		vec3i plus_assign_scalar(79815, 315, 95);
		plus_assign_scalar += 85.467835f;
		CHECK(plus_assign_scalar.x == 79900);
		CHECK(plus_assign_scalar.y == 400);
		CHECK(plus_assign_scalar.z == 180);

		vec3i plus_assign_dest(1111, 8888, 500);
		vec3f plus_assign_src(-0.98648f, 1112.9f, -500);
		plus_assign_dest += plus_assign_src;
		CHECK(plus_assign_dest.x == 1111);
		CHECK(plus_assign_dest.y == 10000);
		CHECK(plus_assign_dest.z == 0);
	}

	SUBCASE("unary operators: -=") {
		vec3i minus_assign_scalar(100, -100, 400);
		minus_assign_scalar -= 100;
		CHECK(minus_assign_scalar.x == 0);
		CHECK(minus_assign_scalar.y == -200);
		CHECK(minus_assign_scalar.z == 300);

		vec3i minus_assign_dst(187, 94, 28);
		vec3f minus_assign_src(458.875f, 0.985f, -2);
		minus_assign_dst -= minus_assign_src;
		CHECK(minus_assign_dst.x == -271);
		CHECK(minus_assign_dst.y == 94);
		CHECK(minus_assign_dst.z == 30);
	}

	SUBCASE("unary operators: *=") {
		vec3f multiply_assign_scalar(2.5, 8.75, 1);
		multiply_assign_scalar *= 0.75f;
		CHECK(multiply_assign_scalar.x == 1.875f);
		CHECK(multiply_assign_scalar.y == 6.5625f);
		CHECK(multiply_assign_scalar.z == 0.75f);

		vec3f multiply_assign_dst(9784, 1500, 5);
		vec3f multiply_assign_src(-0.1f, 7.5f, -2.f);
		multiply_assign_dst *= multiply_assign_src;
		CHECK(multiply_assign_dst.x == -978.40002f);
		CHECK(multiply_assign_dst.y == 11250.0f);
		CHECK(multiply_assign_dst.z == -10.0f);
	}

	SUBCASE("unary operators: /=") {
		vec3f divide_assign_scalar(32, 64, 96);
		divide_assign_scalar /= 2.f;
		CHECK(divide_assign_scalar.x == 16.f);
		CHECK(divide_assign_scalar.y == 32.f);
		CHECK(divide_assign_scalar.z == 48.f);

		vec3f divide_assign_dst(115477, 1452145, 685);
		vec3f divide_assign_src(20, 450, -4);
		divide_assign_dst /= divide_assign_src;
		CHECK(divide_assign_dst.x == 5773.8501f);
		CHECK(divide_assign_dst.y == 3226.98877f);
		CHECK(divide_assign_dst.z == -171.25);
	}

	SUBCASE("relational operators") {
		CHECK(vec3i(42, -29, 14) < vec3i(59, -19, 18));
		CHECK(vec3i(42, 8, 18) <= vec3i(59, 9, 18));
		CHECK(vec3i(100, 200, 300) > vec3i(99, 199, 299));
		CHECK(vec3i(100, 200, 300) >= vec3i(100, 199, 300));
	}

	SUBCASE("array subscriptors: []") {
		vec3i sub(456, 987, 29);
		CHECK(sub[0] == 456);
		CHECK(sub[1] == 987);
		CHECK(sub[2] == 29);
		#ifdef CT_ASSERT_ENABLED
			CHECK_THROWS(sub[3] == 100);
		#endif
	}

	SUBCASE("unary operators: negate(-) and nonnegate(+)") {
		vec3i a(178, 981, -1488);
		auto b = -a;
		CHECK(b.x == -178);
		CHECK(b.y == -981);
		CHECK(b.z == 1488);
		b = +b;
		CHECK(b.x == -178);
		CHECK(b.y == -981);
		CHECK(b.z == 1488);
	}

	SUBCASE("binary operators: +") {
		vec3i a(0,48,96);
		vec3i b(-32, 48,-64);
		auto r = a + b;
		CHECK(r.x == -32);
		CHECK(r.y == 96);
		CHECK(r.z == 32);
		r = r + 24;
		CHECK(r.x == -8);
		CHECK(r.y == 120);
		CHECK(r.z == 56);
		r = -64 + r;
		CHECK(r.x == -72);
		CHECK(r.y == 56);
		CHECK(r.z == -8);
	}

	SUBCASE("binary operators: -") {
		vec3i a(0,48,96);
		vec3i b(-32, 48,-64);
		auto r = a - b;
		CHECK(r.x == 32);
		CHECK(r.y == 0);
		CHECK(r.z == 160);
		r = r - 24;
		CHECK(r.x == 8);
		CHECK(r.y == -24);
		CHECK(r.z == 136);
		r = -64 - r;
		CHECK(r.x == -72);
		CHECK(r.y == -40);
		CHECK(r.z == -200);
	}

	SUBCASE("binary operators: *") {
		vec3f a(124.f,328.f, -28.f);
		vec3f b(2.75f, -1.5f, -4.f);
		auto r = a * b;
		CHECK(r.x == 341.0f);
		CHECK(r.y == -492.0f);
		CHECK(r.z == 112.0f);
		r = r * 8.5f;
		CHECK(r.x == 2898.5f);
		CHECK(r.y == -4182.0f);
		CHECK(r.z == 952.0f);
		r = 0.1f * r;
		CHECK(r.x == 289.85f);
		CHECK(r.y == -418.20001f);
		CHECK(essentially_equal(r.z, 95.2f));
	}

	SUBCASE("binary operators: /") {
		vec3f a(132.f,-1024.f, 2480);
		vec3f b(2.f, -16.f, 40);
		auto r = a / b;
		CHECK(r.x == 66.f);
		CHECK(r.y == 64.f);
		CHECK(r.z == 62.f);
		r = r / 4.f;
		CHECK(r.x == 16.5f);
		CHECK(r.y == 16.0f);
		CHECK(r.z == 15.5f);
		r = 1.f / r;
		CHECK(essentially_equal(r.x, 0.06061f));
		CHECK(r.y == 0.0625f);
		CHECK(essentially_equal(r.z, 0.06451f));
	}

	SUBCASE("boolean operators: == !=") {
		vec3i a(10, 10, 10);
		vec3i b(10, 10, 10);
		vec3i c(10, 11, 12);
		CHECK(a == b);
		CHECK(a != c);
	}

	SUBCASE("vectors of bool relation: && ||") {
		vec3b a(true, false, true);
		vec3b b(true, false, false);
		vec3b r = a && b;
		CHECK(r.x == true);
		CHECK(r.y == false);
		CHECK(r.z == false);
		r = a || b;
		CHECK(r.x == true);
		CHECK(r.y == false);
		CHECK(r.z == true);
		b.y = true;
		r = a || b;
		CHECK(r.x == true);
		CHECK(r.y == true);
		CHECK(r.z == true);
	}

}
