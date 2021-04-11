
#include "../../commons/math_commons.hpp"

template <typename T>
CONSTEXPR CT_FORCEINLINE void swap(T * a, T * b) {
	T * tmp = a;
	a = b;
	b = tmp;
}

namespace glm {
	template <typename T>
	ct::tmat4<T> inverse(const ct::tmat4<T> & m) {

		const ct::tvec4<T> & col0 = m.col(0);
		const ct::tvec4<T> & col1 = m.col(1);
		const ct::tvec4<T> & col2 = m.col(2);
		const ct::tvec4<T> & col3 = m.col(3);

		T Coef00 = col2[2] * col3[3] - col3[2] * col2[3];
		T Coef02 = col1[2] * col3[3] - col3[2] * col1[3];
		T Coef03 = col1[2] * col2[3] - col2[2] * col1[3];

		T Coef04 = col2[1] * col3[3] - col3[1] * col2[3];
		T Coef06 = col1[1] * col3[3] - col3[1] * col1[3];
		T Coef07 = col1[1] * col2[3] - col2[1] * col1[3];

		T Coef08 = col2[1] * col3[2] - col3[1] * col2[2];
		T Coef10 = col1[1] * col3[2] - col3[1] * col1[2];
		T Coef11 = col1[1] * col2[2] - col2[1] * col1[2];

		T Coef12 = col2[0] * col3[3] - col3[0] * col2[3];
		T Coef14 = col1[0] * col3[3] - col3[0] * col1[3];
		T Coef15 = col1[0] * col2[3] - col2[0] * col1[3];

		T Coef16 = col2[0] * col3[2] - col3[0] * col2[2];
		T Coef18 = col1[0] * col3[2] - col3[0] * col1[2];
		T Coef19 = col1[0] * col2[2] - col2[0] * col1[2];

		T Coef20 = col2[0] * col3[1] - col3[0] * col2[1];
		T Coef22 = col1[0] * col3[1] - col3[0] * col1[1];
		T Coef23 = col1[0] * col2[1] - col2[0] * col1[1];

		ct::tvec4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
		ct::tvec4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
		ct::tvec4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
		ct::tvec4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
		ct::tvec4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
		ct::tvec4<T> Fac5(Coef20, Coef20, Coef22, Coef23);

		ct::tvec4<T> Vec0(col1[0], col0[0], col0[0], col0[0]);
		ct::tvec4<T> Vec1(col1[1], col0[1], col0[1], col0[1]);
		ct::tvec4<T> Vec2(col1[2], col0[2], col0[2], col0[2]);
		ct::tvec4<T> Vec3(col1[3], col0[3], col0[3], col0[3]);

		ct::tvec4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		ct::tvec4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		ct::tvec4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		ct::tvec4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		ct::tvec4<T> SignA(+1, -1, +1, -1);
		ct::tvec4<T> SignB(-1, +1, -1, +1);
		ct::tmat4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		ct::tvec4<T> Row0(Inverse.col(0)[0], Inverse.col(1)[0], Inverse.col(2)[0], Inverse.col(3)[0]);

		ct::tvec4<T> Dot0(col0 * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}
}

namespace euclidean_space {
	template <typename T>
	ct::tmat4<T> inverse(const ct::tmat4<T> & a) {
		T det = a.determinant();
		// there is no inverse if determinant is zero (not likely unless scale is broken)
		if (0.0f == det) {
			//fprintf(stderr, "WARNING. matrix has no determinant. can not invert\n");
			return a;
		}
		det = static_cast<T>(1) / det;
		return ct::tmat4<T>(
		    det * (
			a[9] * a[14] * a[7] - a[13] * a[10] * a[7] +
			a[13] * a[6] * a[11] - a[5] * a[14] * a[11] -
			a[9] * a[6] * a[15] + a[5] * a[10] * a[15]
			),
		    det * (
			a[13] * a[10] * a[3] - a[9] * a[14] * a[3] -
			a[13] * a[2] * a[11] + a[1] * a[14] * a[11] +
			a[9] * a[2] * a[15] - a[1] * a[10] * a[15]
			),
		    det * (
			a[5] * a[14] * a[3] - a[13] * a[6] * a[3] +
			a[13] * a[2] * a[7] - a[1] * a[14] * a[7] -
			a[5] * a[2] * a[15] + a[1] * a[6] * a[15]
			),
		    det * (
			a[9] * a[6] * a[3] - a[5] * a[10] * a[3] -
			a[9] * a[2] * a[7] + a[1] * a[10] * a[7] +
			a[5] * a[2] * a[11] - a[1] * a[6] * a[11]
			),
		    det * (
			a[12] * a[10] * a[7] - a[8] * a[14] * a[7] -
			a[12] * a[6] * a[11] + a[4] * a[14] * a[11] +
			a[8] * a[6] * a[15] - a[4] * a[10] * a[15]
			),
		    det * (
			a[8] * a[14] * a[3] - a[12] * a[10] * a[3] +
			a[12] * a[2] * a[11] - a[0] * a[14] * a[11] -
			a[8] * a[2] * a[15] + a[0] * a[10] * a[15]
			),
		    det * (
			a[12] * a[6] * a[3] - a[4] * a[14] * a[3] -
			a[12] * a[2] * a[7] + a[0] * a[14] * a[7] +
			a[4] * a[2] * a[15] - a[0] * a[6] * a[15]
			),
		    det * (
			a[4] * a[10] * a[3] - a[8] * a[6] * a[3] +
			a[8] * a[2] * a[7] - a[0] * a[10] * a[7] -
			a[4] * a[2] * a[11] + a[0] * a[6] * a[11]
			),
		    det * (
			a[8] * a[13] * a[7] - a[12] * a[9] * a[7] +
			a[12] * a[5] * a[11] - a[4] * a[13] * a[11] -
			a[8] * a[5] * a[15] + a[4] * a[9] * a[15]
			),
		    det * (
			a[12] * a[9] * a[3] - a[8] * a[13] * a[3] -
			a[12] * a[1] * a[11] + a[0] * a[13] * a[11] +
			a[8] * a[1] * a[15] - a[0] * a[9] * a[15]
			),
		    det * (
			a[4] * a[13] * a[3] - a[12] * a[5] * a[3] +
			a[12] * a[1] * a[7] - a[0] * a[13] * a[7] -
			a[4] * a[1] * a[15] + a[0] * a[5] * a[15]
			),
		    det * (
			a[8] * a[5] * a[3] - a[4] * a[9] * a[3] -
			a[8] * a[1] * a[7] + a[0] * a[9] * a[7] +
			a[4] * a[1] * a[11] - a[0] * a[5] * a[11]
			),
		    det * (
			a[12] * a[9] * a[6] - a[8] * a[13] * a[6] -
			a[12] * a[5] * a[10] + a[4] * a[13] * a[10] +
			a[8] * a[5] * a[14] - a[4] * a[9] * a[14]
			),
		    det * (
			a[8] * a[13] * a[2] - a[12] * a[9] * a[2] +
			a[12] * a[1] * a[10] - a[0] * a[13] * a[10] -
			a[8] * a[1] * a[14] + a[0] * a[9] * a[14]
			),
		    det * (
			a[12] * a[5] * a[2] - a[4] * a[13] * a[2] -
			a[12] * a[1] * a[6] + a[0] * a[13] * a[6] +
			a[4] * a[1] * a[14] - a[0] * a[5] * a[14]
			),
		    det * (
			a[4] * a[9] * a[2] - a[8] * a[5] * a[2] +
			a[8] * a[1] * a[6] - a[0] * a[9] * a[6] -
			a[4] * a[1] * a[10] + a[0] * a[5] * a[10]
			));
	}
}

namespace gauss_jordan_a {
	template <typename T>
	ct::tmat4<T> inverse(const ct::tmat4<T> & a) {
		T aug[32];
		T * tmp;
		T * row[4];
		T val;
		int i;
		int k;
		int j = 0;

		for (; j < 4; j++) {

			row[j] = &aug[j * 8];

			for (i = 0; i < 8; i += 1) {
				if (i < 4) {
					//aug[i + j * 8] = a(i, j);
					row[j][i] = a(j, i);
				} else {
					//aug[i + j * 8] = (i % 4 == j) ? 1 : 0;
					row[j][i] = (i % 4 == j) ? 1 : 0;
				}
			}
		}

		// swap the row of matrix,
		for (j = 3; j > 0; j -= 1) {
			if (row[j - 1][0] < row[j][0]) {
				tmp = row[j];
				row[j] = row[j - 1];
				row[j] = tmp;
			}
		}

		// replace a row by sum of itself and a
		// constant multiple of another row of the matrix
		for (j = 0; j < 4; j += 1) {
			for (i = 0; i < 4; i += 1) {
				if (j != i) {
					val = row[i][j] / row[j][j];
					for (k = 0; k < 8; k += 1) {
						row[i][k] -= row[j][k] * val;
					}
				}
			}
		}

		// multiply each row by a nonzero integer
		// divide row element by the diagonal element
		for (j = 0; j < 4; j += 1) {
			val = row[j][j];
			for (i = 0; i < 8; i += 1) {
				row[j][i] = row[j][i] / val;
			}
		}

		return ct::tmat4<T>(
			row[0][4], row[0][5], row[0][6], row[0][7],
			row[1][4], row[1][5], row[1][6], row[1][7],
			row[2][4], row[2][5], row[2][6], row[2][7],
			row[3][4], row[3][5], row[3][6], row[3][7]
			);

	}
}

namespace gauss_jordan_b {


	template <typename T>
	ct::tmat4<T> inverse(const ct::tmat4<T> & a) {
		ct::tvec4<T> augmented[4][2];
		ct::tvec4<T> * c0, * c1, * c2, * c3;

		c0 = augmented[0];
		c1 = augmented[1];
		c2 = augmented[2];
		c3 = augmented[3];

		c0[0] = a.col(0);
		c0[1].set(1.f, 0, 0, 0);

		c1[0] = a.col(1);
		c1[1].set(0.f, 1.f, 0, 0);

		c2[0] = a.col(2);
		c2[1].set(0.f, 0.f, 1.f, 0);

		c3[0] = a.col(3);
		c3[1].set(0.f, 0.f, 0.f, 1.f);

		if (fabsf(c3[0][0]) > fabsf(c2[0][0])) {
			swap(c3, c2);
		}

		if (fabsf(c2[0][0]) > fabsf(c1[0][0])) {
			swap(c2, c1);
		}

		if (fabsf(c1[0][0]) > fabsf(c0[0][0])) {
			swap(c1, c0);
		}

		if (c0[0][0] == static_cast<T>(0)) {
			return a;
		}

		T m1 = c1[0][0] / c0[0][0];
		T m2 = c2[0][0] / c0[0][0];
		T m3 = c3[0][0] / c0[0][0];

		T d = c0[0][1];
		c1[0][1] -= m1 * d;
		c2[0][1] -= m2 * d;
		c3[0][1] -= m3 * d;

		d = c0[0][2];
		c1[0][2] -= m1 * d;
		c2[0][2] -= m2 * d;
		c3[0][2] -= m3 * d;

		d = c0[0][3];
		c1[0][3] -= m1 * d;
		c2[0][3] -= m2 * d;
		c3[0][3] -= m3 * d;

		d = c0[1][0];
		if (d != 0.0F) {
			c1[1][0] -= m1 * d;
			c2[1][0] -= m2 * d;
			c3[1][0] -= m3 * d;
		}

		d = c0[1][1];
		if (d != 0.0F) {
			c1[1][1] -= m1 * d;
			c2[1][1] -= m2 * d;
			c3[1][1] -= m3 * d;
		}

		d = c0[1][2];
		if (d != 0.0F) {
			c1[1][2] -= m1 * d;
			c2[1][2] -= m2 * d;
			c3[1][2] -= m3 * d;
		}

		d = c0[1][3];
		if (d != 0.0F) {
			c1[1][3] -= m1 * d;
			c2[1][3] -= m2 * d;
			c3[1][3] -= m3 * d;
		}


		if (fabsf(c3[0][1]) > fabsf(c2[0][1])) {
			swap(c3, c2);
		}

		if (fabsf(c2[0][1]) > fabsf(c1[0][1])) {
			swap(c2, c1);
		}

		if (0.0F == c1[0][1]) {
			return a;
		}


		m2 = c2[0][1] / c1[0][1];
		m3 = c3[0][1] / c1[0][1];

		c2[0][2] -= m2 * c1[0][2];
		c3[0][2] -= m3 * c1[0][2];

		c2[0][3] -= m2 * c1[0][3];
		c3[0][3] -= m3 * c1[0][3];

		d = c1[1][0];
		if (d != 0.0F) {
			c2[1][0] -= m2 * d;
			c3[1][0] -= m3 * d;
		}

		d = c1[1][1];
		if (d != 0.0F) {
			c2[1][1] -= m2 * d;
			c3[1][1] -= m3 * d;
		}

		d = c1[1][2];
		if (d != 0.0F) {
			c2[1][2] -= m2 * d;
			c3[1][2] -= m3 * d;
		}

		d = c1[1][3];
		if (d != 0.0F) {
			c2[1][3] -= m2 * d;
			c3[1][3] -= m3 * d;
		}

		if (fabsf(c3[0][2]) > fabsf(c2[0][2])) {
			swap(c3, c2);
		}

		if (0.0F == c2[0][2]) {
			return a;
		}

		m3 = c3[0][2] / c2[0][2];

		c3[0][3] -= m3 * c2[0][3];
		c3[1][0] -= m3 * c2[1][0];
		c3[1][1] -= m3 * c2[1][1];
		c3[1][2] -= m3 * c2[1][2];
		c3[1][3] -= m3 * c2[1][3];

		/* last check */
		if (0.0F == c3[0][3]) {
			return a;
		}

		/* now back substitute row 3 */
		d = static_cast<T>(1) / c3[0][3];
		c3[1][0] *= d;
		c3[1][1] *= d;
		c3[1][2] *= d;
		c3[1][3] *= d;

		/* now back substitute row 2 */
		d = static_cast<T>(1) / c2[0][2];
		m2 = c2[0][3];
		c2[1][0] = d * (c2[1][0] - c3[1][0] * m2);
		c2[1][1] = d * (c2[1][1] - c3[1][1] * m2);
		c2[1][2] = d * (c2[1][2] - c3[1][2] * m2);
		c2[1][3] = d * (c2[1][3] - c3[1][3] * m2);

		m1 = c1[0][3];
		c1[1][0] -= c3[1][0] * m1;
		c1[1][1] -= c3[1][1] * m1;
		c1[1][2] -= c3[1][2] * m1;
		c1[1][3] -= c3[1][3] * m1;

		m1 = c0[0][3];
		c0[1][0] -= c3[1][0] * m1;
		c0[1][1] -= c3[1][1] * m1;
		c0[1][2] -= c3[1][2] * m1;
		c0[1][3] -= c3[1][3] * m1;

		/* now back substitute row 1 */
		d = static_cast<T>(1) / c1[0][1];
		m1 = c1[0][2];
		c1[1][0] = d * (c1[1][0] - c2[1][0] * m1);
		c1[1][1] = d * (c1[1][1] - c2[1][1] * m1);
		c1[1][2] = d * (c1[1][2] - c2[1][2] * m1);
		c1[1][3] = d * (c1[1][3] - c2[1][3] * m1);

		m1 = c0[0][2];
		c0[1][0] -= c2[1][0] * m1;
		c0[1][1] -= c2[1][1] * m1;
		c0[1][2] -= c2[1][2] * m1;
		c0[1][3] -= c2[1][3] * m1;

		/* now back substitute row 0 */
		d = 1.0F / c0[0][0];
		m1 = c0[0][1];

		c0[1][0] = d * (c0[1][0] - c1[1][0] * m1);
		c0[1][1] = d * (c0[1][1] - c1[1][1] * m1);
		c0[1][2] = d * (c0[1][2] - c1[1][2] * m1);
		c0[1][3] = d * (c0[1][3] - c1[1][3] * m1);


		return ct::tmat4<T>(
			c0[1][0], c0[1][1], c0[1][2], c0[1][3],
			c1[1][0], c1[1][1], c1[1][2], c1[1][3],
			c2[1][0], c2[1][1], c2[1][2], c2[1][3],
			c3[1][0], c3[1][1], c3[1][2], c3[1][3]
			);
	}
}
