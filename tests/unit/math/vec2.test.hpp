
#include <doctest.h>

#include "../../commons/math_commons.hpp"

TEST_CASE("math/vec2") {

	SUBCASE("default constructors") {
		vec2f def_zero;
		CHECK(def_zero.x == 0.f);
		CHECK(def_zero.y == 0.f);

		vec2f copy_src(14.78f, 56.3467f);
		vec2f copy_dest(copy_src);
		CHECK(copy_dest.x == 14.78f);
		CHECK(copy_dest.y == 56.3467f);
	}

	SUBCASE("explicit constructors") {
		vec2f expl_vec(42.f,13.f);
		CHECK(expl_vec.x == 42.f);
		CHECK(expl_vec.y == 13.f);

		vec2f expl_scalar(84.f);
		CHECK(expl_scalar.x == 84.f);
		CHECK(expl_scalar.y == 84.f);
	}


	SUBCASE("conversion constructors") {
		vec2f convert_from_uint(8u, 9u);
		CHECK(convert_from_uint.x == 8.f);
		CHECK(convert_from_uint.y == 9.f);

		vec2i i32_vec(1024, 800);
		vec2f f32_vec(i32_vec);
		CHECK(f32_vec.x == 1024.f);
		CHECK(f32_vec.y == 800.f);
	}

	SUBCASE("assign operators: =") {
		vec2i assign_src(1400.45f,900);
		auto assign_dst = assign_src;
		CHECK(assign_dst.x == 1400);
		CHECK(assign_dst.y == 900);

		vec2f assign_convert_src(150.893245f,1984.123459f);
		vec2i assign_convert_dst = assign_convert_src;
		CHECK(assign_convert_dst.x == 150);
		CHECK(assign_convert_dst.y == 1984);
	}

	SUBCASE("unary operators: +=") {
		vec2i plus_assign_scalar(79815, 315);
		plus_assign_scalar += 85.467835f;
		CHECK(plus_assign_scalar.x == 79900);
		CHECK(plus_assign_scalar.y == 400);

		vec2i plus_assign_dest(1111, 8888);
		vec2f plus_assign_src(-0.98648f, 1112.9f);
		plus_assign_dest += plus_assign_src;
		CHECK(plus_assign_dest.x == 1111);
		CHECK(plus_assign_dest.y == 10000);
	}

	SUBCASE("unary operators: -=") {
		vec2i minus_assign_scalar(100, -100);
		minus_assign_scalar -= 100;
		CHECK(minus_assign_scalar.x == 0);
		CHECK(minus_assign_scalar.y == -200);

		vec2i minus_assign_dst(187, 94);
		vec2f minus_assign_src(458.875f, 0.985f);
		minus_assign_dst -= minus_assign_src;
		CHECK(minus_assign_dst.x == -271);
		CHECK(minus_assign_dst.y == 94);
	}

	SUBCASE("unary operators: *=") {
		vec2f multiply_assign_scalar(2.5, 8.75);
		multiply_assign_scalar *= 0.75f;
		CHECK(multiply_assign_scalar.x == 1.875f);
		CHECK(multiply_assign_scalar.y == 6.5625f);

		vec2f multiply_assign_dst(9784, 1500);
		vec2f multiply_assign_src(-0.1f, 7.5f);
		multiply_assign_dst *= multiply_assign_src;
		CHECK(multiply_assign_dst.x == -978.40002f);
		CHECK(multiply_assign_dst.y == 11250.0f);
	}

	SUBCASE("unary operators: /=") {
		vec2f divide_assign_scalar(32, 64);
		divide_assign_scalar /= 2.f;
		CHECK(divide_assign_scalar.x == 16.f);
		CHECK(divide_assign_scalar.y == 32.f);

		vec2f divide_assign_dst(115477, 1452145);
		vec2f divide_assign_src(20, 450);
		divide_assign_dst /= divide_assign_src;
		CHECK(divide_assign_dst.x == 5773.8501f);
		CHECK(divide_assign_dst.y == 3226.98877f);
	}

	SUBCASE("relational operators") {
		CHECK(vec2i(42, -29) < vec2i(59, -19));
		CHECK(vec2i(42, 8) <= vec2i(59, 9));
		CHECK(vec2i(100, 200) > vec2i(99, 199));
		CHECK(vec2i(100, 200) >= vec2i(100, 199));
	}

	SUBCASE("array subscriptors: []") {
		vec2i sub(456, 987);
		CHECK(sub[0] == 456);
		CHECK(sub[1] == 987);
		#ifdef CT_ASSERT_ENABLED
			CHECK_THROWS(sub[2] == 100);
		#endif
	}

	SUBCASE("unary operators: negate(-) and nonnegate(+)") {
		vec2i a(178, 981);
		auto b = -a;
		CHECK(b.x == -178);
		CHECK(b.y == -981);
		b = -b;
		b = +b;
		CHECK(b.x == 178);
		CHECK(b.y == 981);
	}

	SUBCASE("binary operators: +") {
		vec2i a(0,48);
		vec2i b(-32, 48);
		auto r = a + b;
		CHECK(r.x == -32);
		CHECK(r.y == 96);
		r = r + 24;
		CHECK(r.x == -8);
		CHECK(r.y == 120);
		r = -64 + r;
		CHECK(r.x == -72);
		CHECK(r.y == 56);
	}

	SUBCASE("binary operators: -") {
		vec2i a(0,48);
		vec2i b(-32, 48);
		auto r = a - b;
		CHECK(r.x == 32);
		CHECK(r.y == 0);
		r = r - 24;
		CHECK(r.x == 8);
		CHECK(r.y == -24);
		r = -64 - r;
		CHECK(r.x == -72);
		CHECK(r.y == -40);
	}

	SUBCASE("binary operators: *") {
		vec2f a(124.f,328.f);
		vec2f b(2.75f, -1.5f);
		auto r = a * b;
		CHECK(r.x == 341.0f);
		CHECK(r.y == -492.0f);
		r = r * 8.5f;
		CHECK(r.x == 2898.5f);
		CHECK(r.y == -4182.0f);
		r = 0.1f * r;
		CHECK(r.x == 289.85f);
		CHECK(r.y == -418.20001f);
	}

	SUBCASE("binary operators: /") {
		vec2f a(132.f,-1024.f);
		vec2f b(2.f, -16.f);
		auto r = a / b;
		CHECK(r.x == 66.f);
		CHECK(r.y == 64.f);
		r = r / 4.f;
		CHECK(r.x == 16.5f);
		CHECK(r.y == 16.0f);
		r = 1.f / r;
		CHECK(essentially_equal(r.x, 0.06061f));
		CHECK(r.y == 0.0625f);
	}

	SUBCASE("boolean operators: == !=") {
		vec2i a(10, 10);
		vec2i b(10, 10);
		vec2i c(10, 11);
		CHECK(a == b);
		CHECK(a != c);
	}

	SUBCASE("vectors of bool relation: && ||") {
		vec2b a(true, false);
		vec2b b(true, false);
		vec2b r = a && b;
		CHECK(r.x == true);
		CHECK(r.y == false);
		r = a || b;
		CHECK(r.x == true);
		CHECK(r.y == false);
		b.y = true;
		r = a || b;
		CHECK(r.x == true);
		CHECK(r.y == true);
	}

}
