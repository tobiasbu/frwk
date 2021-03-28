#include <doctest.h>
#include "commons.hpp"

TEST_CASE("math/vec4") {

	SUBCASE("default constructors") {
		vec4f def_zero;
		CHECK(def_zero.x == 0.f);
		CHECK(def_zero.y == 0.f);
		CHECK(def_zero.z == 0.f);
		CHECK(def_zero.w == 0.f);

		vec4f copy_src(14.78f, 56.3467f, -42.0f, 148.0f);
		vec4f copy_dest(copy_src);
		CHECK(copy_dest.x == 14.78f);
		CHECK(copy_dest.y == 56.3467f);
		CHECK(copy_dest.z == -42.0f);
		CHECK(copy_dest.w == 148.f);
	}

	SUBCASE("explicit constructors") {
		vec4f expl_vec(42.f, 13.f, 196.f, -984.5f);
		CHECK(expl_vec.x == 42.f);
		CHECK(expl_vec.y == 13.f);
		CHECK(expl_vec.z == 196.f);
		CHECK(expl_vec.w == -984.5f);

		vec4f expl_scalar(84.f);
		CHECK(expl_scalar.x == 84.f);
		CHECK(expl_scalar.y == 84.f);
		CHECK(expl_scalar.z == 84.f);
		CHECK(expl_scalar.w == 84.f);
	}

	SUBCASE("conversion constructors - scalar") {
		vec4f convert_from_a(4458ull);
		CHECK(convert_from_a.x == 4458.f);
		CHECK(convert_from_a.y == 4458.f);
		CHECK(convert_from_a.z == 4458.f);
		CHECK(convert_from_a.w == 4458.f);

		vec4f convert_from_d(8u, 9u, 17, 34.45);
		CHECK(convert_from_d.x == 8.f);
		CHECK(convert_from_d.y == 9.f);
		CHECK(convert_from_d.z == 17.f);
		CHECK(convert_from_d.w == 34.45f);
	}

	SUBCASE("conversion constructors - vec2") {
		vec2f from_vec2_a(64.f, -1284.45f);
		vec2f from_vec2_b(53.55f, -488.f);
		vec4f dst(from_vec2_a, from_vec2_b);
		CHECK(dst.x == 64.f);
		CHECK(dst.y == -1284.45f);
		CHECK(dst.z == 53.55f);
		CHECK(dst.w == -488.f);

		vec2i from_vec2_a_2(196, -222);
		vec2b from_vec2_b_2(true, false);
		vec4f dst_2(from_vec2_a_2, from_vec2_b_2);
		CHECK(dst_2.x == 196.f);
		CHECK(dst_2.y == -222.f);
		CHECK(dst_2.z == 1.f);
		CHECK(dst_2.w == 0.f);
	}

	SUBCASE("conversion constructors - vec3") {
		vec3f from_vec3_a(64.f, -1284.45f, -456);
		vec4f dst(from_vec3_a, 145.8f);
		CHECK(dst.x == 64.f);
		CHECK(dst.y == -1284.45f);
		CHECK(dst.z == -456.f);
		CHECK(dst.w == 145.8f);

		vec3i from_vec3_b(196, -222, 6423);
		vec4f dst_b(from_vec3_b);
		CHECK(dst_b.x == 196.f);
		CHECK(dst_b.y == -222.f);
		CHECK(dst_b.z == 6423.f);
		CHECK(dst_b.w == 0.f);
	}

	SUBCASE("conversion constructors - vec4") {
		vec4i from_vec4_a(90, 100u, -190, 80.45);
		vec4f dst(from_vec4_a);
		CHECK(dst.x == 90.f);
		CHECK(dst.y == 100.f);
		CHECK(dst.z == -190.f);
		CHECK(dst.w == 80.0f);
	}

	SUBCASE("assign operators: =") {
		vec4i assign_src(1400.45f,900, 896, 750);
		auto assign_dst = assign_src;
		CHECK(assign_dst.x == 1400);
		CHECK(assign_dst.y == 900);
		CHECK(assign_dst.z == 896);
		CHECK(assign_dst.w == 750);

		vec4f assign_convert_src(150.893245f,1984.123459f, 4.23455f, 50.f);
		assign_dst = assign_convert_src;
		CHECK(assign_dst.x == 150);
		CHECK(assign_dst.y == 1984);
		CHECK(assign_dst.z == 4);
		CHECK(assign_dst.w == 50);
	}

	SUBCASE("unary operators: +=") {
		vec4i plus_assign_scalar(79815, 315, 95, -80);
		plus_assign_scalar += 85.467835f;
		CHECK(plus_assign_scalar.x == 79900);
		CHECK(plus_assign_scalar.y == 400);
		CHECK(plus_assign_scalar.z == 180);
		CHECK(plus_assign_scalar.w == 5);

		vec4i plus_assign_dest(1111, 8888, 500, 1253);
		vec4f plus_assign_src(-0.98648f, 1112.9f, -500, -1053);
		plus_assign_dest += plus_assign_src;
		CHECK(plus_assign_dest.x == 1111);
		CHECK(plus_assign_dest.y == 10000);
		CHECK(plus_assign_dest.z == 0);
		CHECK(plus_assign_dest.w == 200);
	}

	SUBCASE("unary operators: -=") {
		vec4i minus_assign_scalar(100, -100, 400, -500);
		minus_assign_scalar -= 100;
		CHECK(minus_assign_scalar.x == 0);
		CHECK(minus_assign_scalar.y == -200);
		CHECK(minus_assign_scalar.z == 300);
		CHECK(minus_assign_scalar.w == -600);

		vec4i minus_assign_dst(187, 94, 28, 4);
		vec4f minus_assign_src(458.875f, 0.985f, -2, -4.5f);
		minus_assign_dst -= minus_assign_src;
		CHECK(minus_assign_dst.x == -271);
		CHECK(minus_assign_dst.y == 94);
		CHECK(minus_assign_dst.z == 30);
		CHECK(minus_assign_dst.w == 8);
	}

	SUBCASE("unary operators: *=") {
		vec4f multiply_assign_scalar(2.5, 8.75, 1, -6.68f);
		multiply_assign_scalar *= 0.75f;
		CHECK(multiply_assign_scalar.x == 1.875f);
		CHECK(multiply_assign_scalar.y == 6.5625f);
		CHECK(multiply_assign_scalar.z == 0.75f);
		CHECK(approximately_equal(multiply_assign_scalar.w, -5.01f));

		vec4f multiply_assign_dst(9784, 1500, 5, -150);
		vec4f multiply_assign_src(-0.1f, 7.5f, -2.f, 5);
		multiply_assign_dst *= multiply_assign_src;
		CHECK(multiply_assign_dst.x == -978.40002f);
		CHECK(multiply_assign_dst.y == 11250.0f);
		CHECK(multiply_assign_dst.z == -10.0f);
		CHECK(multiply_assign_dst.w == -750.0f);
	}

	SUBCASE("unary operators: /=") {
		vec4f divide_assign_scalar(32, 64, 96, 192);
		divide_assign_scalar /= 2.f;
		CHECK(divide_assign_scalar.x == 16.f);
		CHECK(divide_assign_scalar.y == 32.f);
		CHECK(divide_assign_scalar.z == 48.f);
		CHECK(divide_assign_scalar.w == 96.f);

		vec4f divide_assign_dst(115477, 1452145, 685, 320);
		vec4f divide_assign_src(20, 450, -4, 2);
		divide_assign_dst /= divide_assign_src;
		CHECK(divide_assign_dst.x == 5773.8501f);
		CHECK(divide_assign_dst.y == 3226.98877f);
		CHECK(divide_assign_dst.z == -171.25f);
		CHECK(divide_assign_dst.w == 160.f);
	}

		SUBCASE("relational operators") {
		CHECK(vec3i(42, -29, 14) < vec3i(59, -19, 18));
		CHECK(vec3i(42, 8, 18) <= vec3i(59, 9, 18));
		CHECK(vec3i(100, 200, 300) > vec3i(99, 199, 299));
		CHECK(vec3i(100, 200, 300) >= vec3i(100, 199, 300));
	}

	SUBCASE("array subscriptors: []") {
		vec4i sub(456, 987, 29, -888);
		CHECK(sub[0] == 456);
		CHECK(sub[1] == 987);
		CHECK(sub[2] == 29);
		CHECK(sub[3] == -888);
		#ifdef CT_ASSERT_ENABLED
			CHECK_THROWS(sub[5] == 100);
		#endif
	}

	SUBCASE("unary operators: negate(-) and nonnegate(+)") {
		vec4i a(178, 981, -1488, -5);
		auto b = -a;
		CHECK(b.x == -178);
		CHECK(b.y == -981);
		CHECK(b.z == 1488);
		CHECK(b.w == 5);
		b = +b;
		CHECK(b.x == -178);
		CHECK(b.y == -981);
		CHECK(b.z == 1488);
		CHECK(b.w == 5);
	}

	SUBCASE("binary operators: +") {
		vec4i a(0, 48, 96, 192);
		vec4i b(-32, 48, -64, 80);
		auto r = a + b;
		CHECK(r.x == -32);
		CHECK(r.y == 96);
		CHECK(r.z == 32);
		CHECK(r.w == 272);
		r = r + 24;
		CHECK(r.x == -8);
		CHECK(r.y == 120);
		CHECK(r.z == 56);
		CHECK(r.w == 296);
		r = -64 + r;
		CHECK(r.x == -72);
		CHECK(r.y == 56);
		CHECK(r.z == -8);
		CHECK(r.w == 232);
	}

	SUBCASE("binary operators: -") {
		vec4i a(0, 48, 96, 192);
		vec4i b(-32, 48, -64, 80);
		auto r = a - b;
		CHECK(r.x == 32);
		CHECK(r.y == 0);
		CHECK(r.z == 160);
		CHECK(r.w == 112);
		r = r - 24;
		CHECK(r.x == 8);
		CHECK(r.y == -24);
		CHECK(r.z == 136);
		CHECK(r.w == 88);
		r = -64 - r;
		CHECK(r.x == -72);
		CHECK(r.y == -40);
		CHECK(r.z == -200);
		CHECK(r.w == -152);
	}

	SUBCASE("binary operators: *") {
		vec4f a(124.f,328.f, -28.f, 999.f);
		vec4f b(2.75f, -1.5f, -4.f, 9.f);
		auto r = a * b;
		CHECK(r.x == 341.0f);
		CHECK(r.y == -492.0f);
		CHECK(r.z == 112.0f);
		CHECK(r.w == 8991);
		r = r * 8.5f;
		CHECK(r.x == 2898.5f);
		CHECK(r.y == -4182.0f);
		CHECK(r.z == 952.0f);
		CHECK(r.w == 76423.5f);
		r = 0.1f * r;
		CHECK(r.x == 289.85f);
		CHECK(r.y == -418.20001f);
		CHECK(essentially_equal(r.z, 95.2f));
		CHECK(r.w == 7642.35f);
	}

	SUBCASE("binary operators: /") {
		vec4f a(132.f,-1024.f, 2480, 7380.f);
		vec4f b(2.f, -16.f, 40.f, 123.f);
		auto r = a / b;
		CHECK(r.x == 66.f);
		CHECK(r.y == 64.f);
		CHECK(r.z == 62.f);
		CHECK(r.w == 60.f);
		r = r / 4.f;
		CHECK(r.x == 16.5f);
		CHECK(r.y == 16.0f);
		CHECK(r.z == 15.5f);
		CHECK(r.w == 15.f);
		r = 1.f / r;
		CHECK(essentially_equal(r.x, 0.06061f));
		CHECK(r.y == 0.0625f);
		CHECK(essentially_equal(r.z, 0.06451f));
		CHECK(essentially_equal(r.w, 0.066666665f));
	}

	SUBCASE("boolean operators: == !=") {
		vec4i a(10);
		vec4i b(10, 10, 10, 10);
		vec4i c(10, 11, 12, 13);
		CHECK(a == b);
		CHECK(a != c);
	}

	SUBCASE("vectors of bool relation: && ||") {
		vec4b a(true, false, true, false);
		vec4b b(true, false, false, true);
		vec4b r = a && b;
		CHECK(r.x == true);
		CHECK(r.y == false);
		CHECK(r.z == false);
		CHECK(r.w == false);
		r = a || b;
		CHECK(r.x == true);
		CHECK(r.y == false);
		CHECK(r.z == true);
		CHECK(r.w == true);
		b.y = true;
		r = a || b;
		CHECK(r.x == true);
		CHECK(r.y == true);
		CHECK(r.z == true);
		CHECK(r.w == true);
	}

}
