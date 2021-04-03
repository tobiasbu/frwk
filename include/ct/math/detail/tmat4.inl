#include "tmat4.hpp"

namespace ct {

	template <typename T>
	CT_FORCEINLINE CONSTEXPR tmat4<T>::tmat4() {
		m[0] = 0;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;
		m[4] = 0;
		m[5] = 0;
		m[6] = 0;
		m[7] = 0;
		m[8] = 0;
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR tmat4<T>::tmat4(const tmat4<T> & other) {
		m[0] = other.m[0];
		m[1] = other.m[1];
		m[2] = other.m[2];
		m[3] = other.m[3];

		m[4] = other.m[4];
		m[5] = other.m[5];
		m[6] = other.m[6];
		m[7] = other.m[7];

		m[8] = other.m[8];
		m[9] = other.m[9];
		m[10] = other.m[10];
		m[11] = other.m[11];

		m[12] = other.m[12];
		m[13] = other.m[13];
		m[14] = other.m[14];
		m[15] = other.m[15];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR tmat4<T>::tmat4(
		T m00,T m10,T m20,T m30,
		T m01,T m11,T m21,T m31,
		T m02,T m12,T m22,T m32,
	    T m03,T m13,T m23,T m33)
	{
		m[0] = m00;
		m[1] = m10;
		m[2] = m20;
		m[3] = m30;

		m[4] = m01;
		m[5] = m11;
		m[6] = m21;
		m[7] = m31;

		m[8] = m02;
		m[9] = m12;
		m[10] = m22;
		m[11] = m32;

		m[12] = m03;
		m[13] = m13;
		m[14] = m23;
		m[15] = m33;
	}

	template <typename T>
	template <typename M00,typename M10,typename M20,typename M30,
	    typename M01, typename M11, typename M21, typename M31,
		typename M02, typename M12, typename M22, typename M32,
	    typename M03, typename M13, typename M23, typename M33>
	CT_FORCEINLINE CONSTEXPR tmat4<T>::tmat4(
		M00 m00, M10 m10, M20 m20, M30 m30,
		M01 m01, M11 m11, M21 m21, M31 m31,
		M02 m02, M12 m12, M22 m22, M32 m32,
		M03 m03, M13 m13, M23 m23, M33 m33)
	{
		m[0] = static_cast<T>(m00);
		m[1] = static_cast<T>(m10);
		m[2] = static_cast<T>(m20);
		m[3] = static_cast<T>(m30);

		m[4] = static_cast<T>(m01);
		m[5] = static_cast<T>(m11);
		m[6] = static_cast<T>(m21);
		m[7] = static_cast<T>(m31);

		m[8] = static_cast<T>(m02);
		m[9] = static_cast<T>(m12);
		m[10] = static_cast<T>(m22);
		m[11] = static_cast<T>(m32);

		m[12] = static_cast<T>(m03);
		m[13] = static_cast<T>(m13);
		m[14] = static_cast<T>(m23);
		m[15] = static_cast<T>(m33);
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR void  tmat4<T>::set(
		T m00, T m10, T m20, T m30,
	    T m01, T m11, T m21, T m31,
	    T m02, T m12, T m22, T m32,
	    T m03, T m13, T m23, T m33)
	{
		m[0] = m00;
		m[1] = m10;
		m[2] = m20;
		m[3] = m30;

		m[4] = m01;
		m[5] = m11;
		m[6] = m21;
		m[7] = m31;

		m[8] = m02;
		m[9] = m12;
		m[10] = m22;
		m[11] = m32;

		m[12] = m03;
		m[13] = m13;
		m[14] = m23;
		m[15] = m33;
	}

	template <typename T>
	CONSTEXPR tmat4<T>::tmat4(
		const column_type & col_0,
		const column_type & col_1,
		const column_type & col_2,
		const column_type & col_3)
	{
		column[0] = col_0;
		column[1] = col_1;
		column[2] = col_2;
		column[3] = col_3;
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR typename tmat4<T>::column_type & tmat4<T>::col(const u32 & index) {
		__CT_MATH_ASSERT(index >= 0 && index < 4, "ct::tmat4<T>: Can not access column at index %d", index);
		return column[index];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR const typename tmat4<T>::column_type & tmat4<T>::col(const u32 & index) const {
		__CT_MATH_ASSERT(index >= 0 && index < 4, "ct::tmat4<T>: Can not access column at index %d", index);
		return column[index];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR T tmat4<T>::determinant() const {
		return
		// m00
		m[0] * m[5] * m[10] * m[15] - m[0] * m[5] * m[14] * m[11] - //
		m[0] * m[9] * m[6] * m[15] + m[0] * m[9] * m[14] * m[7] +   //
		m[0] * m[13] * m[6] * m[11] - m[0] * m[13] * m[10] * m[7] - //
		// m01
		m[4] * m[1] * m[10] * m[15] + m[4] * m[1] * m[14] * m[11] + //
		m[4] * m[9] * m[2] * m[15] - m[4] * m[9] * m[14] * m[3] -   //
		m[4] * m[13] * m[2] * m[11] + m[4] * m[13] * m[10] * m[3] + //
		// m02
		m[8] * m[1] * m[6] * m[15] - m[8] * m[1] * m[14] * m[7] -   //
		m[8] * m[5] * m[2] * m[15] + m[8] * m[5] * m[14] * m[3] +   //
		m[8] * m[13] * m[2] * m[7] - m[8] * m[13] * m[6] * m[3] -
		// m03
		m[12] * m[1] * m[6] * m[11] + m[12] * m[1] * m[10] * m[7] + //
		m[12] * m[5] * m[2] * m[11] - m[12] * m[5] * m[10] * m[3] - //
		m[12] * m[9] * m[2] * m[7] + m[12] * m[9] * m[6] * m[3];
	}

	template <typename T>
	CONSTEXPR tmat4<T> tmat4<T>::inverse() const {
		T det = determinant();
		if (det == 0) {
			return *this;
		}
		det = static_cast<T>(1) / det;

		tmat4<T> inverse;

		inverse.m[0] = 0;
	}

	// Array Subscriptor

	template <typename T>
	CT_FORCEINLINE CONSTEXPR typename T & tmat4<T>::operator[](const u32 & index) {
		__CT_MATH_ASSERT(index >= 0 && index < 16, "ct::tmat4<T>: Can not access element at index %d", index);
		return m[index];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR const typename T & tmat4<T>::operator[](const u32 & index) const {
		__CT_MATH_ASSERT(index >= 0 && index < 16, "ct::tmat4<T>: Can not access element at index %d", index);
		return m[index];
	}


	template <typename T>
	CT_FORCEINLINE CONSTEXPR T * tmat4<T>::operator()() {
		return &m[0];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR const T * tmat4<T>::operator()() const {
		return &m[0];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR T & tmat4<T>::operator()(const u32 & index) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 16, "ct::tmat4<T>: Can not access element at index %d", index);
		return m[index];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR const T & tmat4<T>::operator()(const u32 & index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 16, "ct::tmat4<T>: Can not access element at index %d", index);
		return m[index];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR const T & tmat4<T>::operator()(const u32 & x, const u32 & y) const {
		__CT_MATH_ASSERT(x >= 0 && x < 4 && y >= 0 && y < 4, "ct::tmat4<T> Can not access element at position [%d, %d]", x, y);
		return m[y + x * 4];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR T & tmat4<T>::operator()(const u32 & x, const u32 & y) {
		__CT_MATH_ASSERT(x >= 0 && x < 4 && y >= 0 && y < 4, "ct::tmat4<T>: Can not access element at position [%d, %d]", x, y);
		return m[y + x * 4];
	}

	// *

	template <typename T>
	CT_FORCEINLINE CONSTEXPR tmat4<T> operator*(const tmat4<T> & mat, T scalar) {
		return tmat4<T>(mat.col(0) * scalar, mat.col(1) * scalar, mat.col(2) * scalar, mat.col(3) * scalar);
	}



} // namespace ct
