
#include <doctest.h>
#include "commons.hpp"

namespace t {
	bool approximately_equals(const mat3 & a, const mat3 & b, float epsilon = 0.0001) {
		for (int i = 0; i < 3; i += 1) {
			if (!approximately_equal(a[i], b[i])) {
				return false;
			}
		}
		return true;
	}
	bool equals(const mat3 & a, const mat3 & b) {
		for (int i = 0; i < 3; i += 1) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		return true;
	}
}


TEST_CASE("math/mat3") {

	SUBCASE("default and explicit constructors") {
		mat3 zero;
		CHECK(t::equals(zero, mat3(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f)));

		mat3 identity(1.0f);
		CHECK(t::equals(identity, mat3(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f)));

		identity(0) = 16;
		identity(1) = 24;
		identity(2) = 32;
		identity(5) = 56;

		mat3 copy_dst(identity);
		CHECK(t::equals(copy_dst, mat3(16.f, 24.f, 32.f, 0.f, 1.f, 56.f, 0.f, 0.f, 1.f)));

		mat3 vec_ctor(vec3f(1, 2, 3), vec3f(4, 5, 6), vec3f(7, 8, 9));
		CHECK(t::equals(vec_ctor, mat3(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f)));

	}

	SUBCASE("assign operator =") {
		mat3 assign_src(8.f, 4.f, 8.f, -6.f, 14.f, 18.f, 64.f, -312.5f, 12000.f);
		mat3 assign_dst(1.0f);
		assign_src = assign_dst;
		CHECK(t::equals(assign_src, assign_dst));
	}

	SUBCASE("unary operator +=") {
		mat3 mat_dst(10, 20, 40, 80, 160, 320, 640, 1280, 2560);
		mat_dst += 1000;
		CHECK(t::equals(mat_dst, mat3(1010, 1020, 1040, 1080, 1160, 1320, 1640, 2280, 3560)));
		mat3 plus_assign_mat(-10, -20, -40, 20, 40, 80, -40, -80, -60);
		mat_dst += plus_assign_mat;
		CHECK(t::equals(mat_dst, mat3(1000, 1000, 1000, 1100, 1200, 1400, 1600, 2200, 3500)));
	}

	SUBCASE("unary operator -=") {
		mat3 mat_dst(10, 20, 40, 80, 160, 320, 640, 1280, 2560);
		mat_dst -= 1000;
		CHECK(t::equals(mat_dst, mat3(-990, -980, -960, -920, -840, -680, -360, 280, 1560)));
		mat3 minus_assign_mat(-10, -20, -40, 20, 40, 80, -40, -80, -60);
		mat_dst -= minus_assign_mat;
		CHECK(t::equals(mat_dst, mat3(-980, -960, -920, -940, -880, -760, -320, 360, 1620)));
	}

	SUBCASE("unary operator *=") {
		mat3 mat_dst(10, 20, 40, 80, 160, 320, 640, 1280, 2560);
		mat_dst *= 32;
		CHECK(t::equals(mat_dst, mat3(320.f, 640.f, 1280.f, 2560.f, 5120.f, 10240.f, 20480.f, 40960.f, 81920.f)));
		mat3 multiply_assign_mat(1, 2, 4, 8, 16, 32, 64, 128, 256);
		mat_dst *= multiply_assign_mat;
		CHECK(t::equals(
		    mat_dst,
		    mat3(87360.f,
		        174720.f,
		        349440.f,
		        698880.f,
		        1397760.f,
		        2795520.f,
		        5591040.f,
		        11182080.f,
		        22364160.f)));
	}

	SUBCASE("unary operator /=") {
		mat3 mat_dst(10, 20, 40, 80, 160, 320, 640, 1280, 2560);
		mat_dst /= 8;
		CHECK(t::equals(mat_dst, mat3(1.25f, 2.5f, 5.f, 10.f, 20.f, 40.f, 80.f, 160.f, 320.f)));
		mat3 division_assign_mat(1.25f, 2, 2, 8, 4, -6, 2.5f, -5, -40);
		mat_dst /= division_assign_mat;
		CHECK(t::approximately_equals(mat_dst,
		                mat3(-4.1743f,
		                     -8.3486f,
		                     -16.6972f,
		                     6.2798f,
		                     12.5596f,
		                     25.1193f,
		                     -3.0459f,
		                     -6.0917f,
		                     -12.1835f)));
	}

	SUBCASE("unary operators: negate(-) and nonnegate(+)") {
		mat3 a(2.0f, -1.f, 0.f, 3.f, -2.f, 1.f, 4.f, -3.f, 2.f);
		auto b = -a;
		CHECK(b[0] == mat3::column_type(-2.f, 1.f, 0.f));
		CHECK(b[1] == mat3::column_type(-3.f, 2.f, -1.f));
		CHECK(b[2] == mat3::column_type(-4.f, 3.f, -2.f));
		b = -b;
		b = +b;
		CHECK(b.get_column(0) == mat3::column_type(2.f, -1.f, 0.f));
		CHECK(b.get_column(1) == mat3::column_type(3.f, -2.f, 1.f));
		CHECK(b.get_column(2) == mat3::column_type(4.f, -3.f, 2.f));
	}

	SUBCASE("binary operators: +") {
		mat3 a(vec3f(0,2,-4), vec3f(6,-8,10), vec3f(-12,14,16));
		mat3 b(vec3f(8,16,24), vec3f(32,40,48), vec3f(56,64,72));
		auto r = a + b;
		CHECK(t::equals(r, mat3(8.f, 18.f, 20.f, 38.f, 32.f, 58.f, 44.f, 78.f, 88.f)));
		r = r + 8.f;
		CHECK(t::equals(r, mat3(16.f, 26.f, 28.f, 46.f, 40.f, 66.f, 52.f, 86.f, 96.f)));
		r = -96.f + r;
		CHECK(t::equals(r, mat3(-80.f, -70.f, -68.f, -50.f, -56.f, -30.f, -44.f, -10.f, 0.f)));
	}

	SUBCASE("binary operators: -") {
		mat3 a(vec3f(0,2,-4), vec3f(6,-8,10), vec3f(-12,14,16));
		mat3 b(vec3f(8,16,24), vec3f(32,40,48), vec3f(56,64,72));
		auto r = a - b;
		CHECK(t::equals(r, mat3(-8.f, -14.f, -28.f, -26.f, -48.f, -38.f, -68.f, -50.f, -56.f)));
		r = r - 8.f;
		CHECK(t::equals(r, mat3(-16.f, -22.f, -36.f, -34.f, -56.f, -46.f, -76.f, -58.f, -64.f)));
		r = -96.f - r;
		CHECK(t::equals(r, mat3(-80.f, -74.f, -60.f, -62.f, -40.f, -50.f, -20.f, -38.f, -32.f)));
	}

	SUBCASE("binary operators: *") {
		mat3 a(vec3f(0,2,-4), vec3f(6,-8,10), vec3f(-12,14,16));
		mat3 b(vec3f(2,2,4), vec3f(-2,-2,-4), vec3f(-2,6,8));
		auto r = a * b;
		CHECK(t::equals(r, mat3(-36.f, 44.f, 76.f, 36.f, -44.f, -76.f, -60.f, 60.f, 196.f)));
		r = r * 2.f;
		CHECK(t::equals(r, mat3(-72.f, 88.f, 152.f, 72.f, -88.f, -152.f, -120.f, 120.f, 392.f)));
		r = -0.25f * r;
		CHECK(t::equals(r, mat3(18.f, -22.f, -38.f, -18.f, 22.f, 38.f, 30.f, -30.f, -98.f)));
	}

	SUBCASE("binary operators: /") {
		mat3 a(vec3f(0,2,-4), vec3f(6,-8,10), vec3f(-12,14,16));
		mat3 b(vec3f(2,2,4), vec3f(2,-2,-4), vec3f(-2,6,8));
		auto r = a / b;
		CHECK(t::approximately_equals(r, mat3(1.5f, -1.5f, 1.5f, -1.5f, 0.5f, 16.5f, 0.f, 1.f, -10.f)));
		r = a / 2.f;
		CHECK(t::equals(r, mat3(0.f, 1.f, -2.f, 3.f, -4.f, 5.f, -6.f, 7.f, 8.f)));
		r = 8.f / b;
		CHECK(t::approximately_equals(r, mat3(4.f, 4.f, 2.f, 4.f, -4.f, -2.f, -4.f, 1.33337f, 1.0f)));
	}

	SUBCASE("get and set column") {
		mat3 mat_column;
		mat_column.set_column(0, vec3f(34, -98, 28));
		mat_column.set_column(1, vec3f(-45, 31, -70));
		mat_column.set_column(2, vec3f(12.5f, 8520.75f, 1.2389f));

		CHECK(mat_column.get_column(0) == vec3f(34.f, -98.f, 28.f));
		CHECK(mat_column.get_column(1) == vec3f(-45, 31.f, -70.f));
		CHECK(mat_column.get_column(2) == vec3f(12.5f, 8520.75f, 1.2389f));

#ifdef CT_ASSERT_ENABLED
		CHECK_THROWS(mat_column.get_column(3));
#endif
	}

	SUBCASE("get and set row") {
		mat3 mat_row;
		mat_row.set_row(0, vec3f(34, -45.f, 12.5f));
		mat_row.set_row(1, vec3f(-98.f, 31.f, 8520.75f));
		mat_row.set_row(2, vec3f(28.f, -70.f, 1.2389f));

		CHECK(mat_row.get_row(0) == vec3f(34.f, -45.f, 12.5f));
		CHECK(mat_row.get_row(1) == vec3f(-98.f, 31.f, 8520.75f));
		CHECK(mat_row.get_row(2) == vec3f(28.f, -70.f, 1.2389f));

#ifdef CT_ASSERT_ENABLED
		CHECK_THROWS(mat_row.get_row(3));
#endif

		mat3 mat_column;
		mat_column.set_column(0, vec3f(34, -98, 28));
		mat_column.set_column(1, vec3f(-45, 31, -70));
		mat_column.set_column(2, vec3f(12.5f, 8520.75f, 1.2389f));

		CHECK(t::equals(mat_row, mat_column));
	}

	SUBCASE("determinant") {
		mat3 mat_det(6, 4, 2, 1, -2, 8, 1, 5, 7);
		CHECK(mat_det.determinant() == -306.f);
		mat_det.set(9, 3, 8, 5, -9, 8, -1, 2, -2);
		CHECK(mat_det.determinant() == 32.f);
	}

	SUBCASE("inverse") {
		mat3 mat_inv(6, 4, 2, 1, -2, 8, 1, 5, 7);

		CHECK(t::approximately_equals(mat_inv.inverse(),
		                              mat3(0.17647058823529411764f,
		                                   0.05882352941176470589f,
		                                   -0.11764705882352941176f,
		                                   -0.003267973856209150325f,
		                                   -0.13071895424836601308f,
		                                   0.15032679738562091503f,
		                                   -0.022875816993464052287f,
		                                   0.084967320261437908495f,
		                                   0.052287581699346405228f)));
		mat_inv.set(9, 3, 8, 5, -9, 8, -1, 2, -2);

		CHECK(t::approximately_equals(mat_inv.inverse(),
		                              mat3(0.0625f,
		                                   0.6875f,
		                                   3.f,
		                                   0.0625f,
		                                   -0.3125f,
		                                   -1.f,
		                                   0.03125f,
		                                   -0.65625f,
		                                   -3.f)));
	}

	SUBCASE("vector multiplication") {
		mat3 mat_dst(6, 4, 2, 1, -2, 8, 1, 5, 7);
		vec3f vec(1,3,5);
		// row vector
		vec3f r = mat_dst * vec;
		CHECK(r == vec3f(14.f, 23.f, 61.f));
		// column vector
		r = vec * mat_dst; 
		CHECK(r == vec3f(28.f, 35.f, 51.f));
	}

}
