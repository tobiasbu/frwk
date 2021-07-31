
namespace ct {

	// Default constructors

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T>::tmat3() {
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
	CT_MATH_FUNC_INL tmat3<T>::tmat3(const tmat3<T> & other) {
		m[0] = other.m[0];
		m[1] = other.m[1];
		m[2] = other.m[2];
		m[3] = other.m[3];
		m[4] = other.m[4];
		m[5] = other.m[5];
		m[6] = other.m[6];
		m[7] = other.m[7];
		m[8] = other.m[8];
	}

	// Explicit constructors

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T>::tmat3(T identity) {
		column[0] = column_type(identity, 0, 0);
		column[1] = column_type(0, identity, 0);
		column[2] = column_type(0, 0, identity);
	}

	template <typename T>
	CT_MATH_FUNC_INL
	tmat3<T>::tmat3(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) {
		m[0] = m00;
		m[1] = m10;
		m[2] = m20;
		m[3] = m01;
		m[4] = m11;
		m[5] = m21;
		m[6] = m02;
		m[7] = m12;
		m[8] = m22;
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T>::tmat3(const column_type & col_0,
	                                 const column_type & col_1,
	                                 const column_type & col_2) {
		column[0] = col_0;
		column[1] = col_1;
		column[2] = col_2;
	}

	template <typename T>
	template <typename M00,
	          typename M10,
	          typename M20,
	          typename M01,
	          typename M11,
	          typename M21,
	          typename M02,
	          typename M12,
	          typename M22>
	CT_MATH_FUNC_INL tmat3<T>::tmat3(M00 m00,
	                                 M10 m10,
	                                 M20 m20,
	                                 M01 m01,
	                                 M11 m11,
	                                 M21 m21,
	                                 M02 m02,
	                                 M12 m12,
	                                 M22 m22) {
		m[0] = static_cast<T>(m00);
		m[1] = static_cast<T>(m10);
		m[2] = static_cast<T>(m20);
		m[3] = static_cast<T>(m01);
		m[4] = static_cast<T>(m11);
		m[5] = static_cast<T>(m21);
		m[6] = static_cast<T>(m02);
		m[7] = static_cast<T>(m12);
		m[8] = static_cast<T>(m22);
	}

	template <typename T>
	template <typename X, typename Y, typename Z>
	CT_MATH_FUNC_INL
	tmat3<T>::tmat3(const tvec3<X> & col_0, const tvec3<Y> & col_1, const tvec3<Z> & col_2) {
		column[0] = column_type(col_0);
		column[1] = column_type(col_1);
		column[2] = column_type(col_2);
	}

	// Functions

	template <typename T>
	CT_MATH_FUNC_INL typename tmat3<T>::column_type & tmat3<T>::col(const u32 & index) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 3, "ct::tmat3<T>: Can not access column at index %d", index);
		return column[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL const typename tmat3<T>::column_type & tmat3<T>::col(const u32 & index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 3, "ct::tmat3<T>: Can not access column at index %d", index);
		return column[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL typename tmat3<T>::column_type tmat3<T>::get_column(u32 index) const {
		__CT_MATH_ASSERT(index >= 0 && index < 3,
		                 "ct::tmat3<T>.get_column: Can not get column with index %d",
		                 index);
		auto i = index * 3;
		return column_type(m[i], m[i + 1], m[i + 2]);
	}

	template <typename T>
	CT_MATH_FUNC_INL typename tmat3<T>::row_type tmat3<T>::get_row(u32 index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 3, "ct::tmat3<T>.get_row: Can not get row with index %d", index);
		return row_type(m[index], m[index + 3], m[index + 6]);
	}

	template <typename T>
	CT_MATH_FUNC_INL void
	tmat3<T>::set(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22) {
		m[0] = m00;
		m[1] = m10;
		m[2] = m20;
		m[3] = m01;
		m[4] = m11;
		m[5] = m21;
		m[6] = m02;
		m[7] = m12;
		m[8] = m22;
	}

	template <typename T>
	CT_MATH_FUNC_INL void tmat3<T>::set_column(u32 index, const column_type & column) {
		__CT_MATH_ASSERT(index >= 0 && index < 3,
		                 "ct::tmat3<T>.set_column: Can not set column with index %d",
		                 index);
		auto i = index * 3;
		m[i] = column.x;
		m[i + 1] = column.y;
		m[i + 2] = column.z;
	}

	template <typename T>
	CT_MATH_FUNC_INL void tmat3<T>::set_row(u32 index, const row_type & row) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 3, "ct::tmat3<T>.set_row: Can not set row with index %d", index);
		m[index] = row.x;
		m[index + 3] = row.y;
		m[index + 6] = row.z;
	}

	template <typename T>
	CT_MATH_FUNC tmat3<T> tmat3<T>::inverse() const {
		// see http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/index.htm
		T det = determinant();
		if (det == 0) { // epsilon
			return *this;
		}
		det = static_cast<T>(1) / det;

		tmat3<T> inverse;
		// m11*m22 - m12*m21
		inverse.m[0] = (m[4] * m[8] - m[7] * m[5]) * det;
		// m12*m20 - m10*m22
		inverse.m[1] = (m[7] * m[2] - m[1] * m[8]) * det;
		// m10*m21 - m11*m20
		inverse.m[2] = (m[1] * m[5] - m[4] * m[2]) * det;
		// m02*m21 - m01*m22
		inverse.m[3] = (m[6] * m[5] - m[3] * m[8]) * det;
		// m00*m22 - m02*m20
		inverse.m[4] = (m[0] * m[8] - m[6] * m[2]) * det;
		// m01*m20 - m00*m21
		inverse.m[5] = (m[3] * m[2] - m[0] * m[5]) * det;
		// m01*m12 - m02*m11
		inverse.m[6] = (m[3] * m[7] - m[6] * m[4]) * det;
		// m02*m10 - m00*m12
		inverse.m[7] = (m[6] * m[1] - m[0] * m[7]) * det;
		// m00*m11 - m01*m10
		inverse.m[8] = (m[0] * m[4] - m[3] * m[1]) * det;

		return inverse;
	}

	template <typename T>
	CT_MATH_FUNC_INL T tmat3<T>::determinant() const {
		// m[0] * (m[4] * m[8] - m[7] * m[5]) -
		// m[3] * (m[1] * m[8] - m[7] * m[2]) +
		// m[6] * (m[1] * m[5] - m[4] * m[2]);
		// m00 * m11 * m22 + m01 * m12 * m20 +
		// m02 * m10 * m21 - m00 * m12 * m21 -
		// m01 * m10 * m22 -  m02 * m11 * m20;
		return m[0] * m[4] * m[8] + m[3] * m[7] * m[2] + m[6] * m[1] * m[5] - m[0] * m[7] * m[5] -
		       m[3] * m[1] * m[8] - m[6] * m[4] * m[2];
	}

	template <typename T>
	CT_MATH_FUNC_INL void tmat3<T>::transpose() {
		set(m[0], m[3], m[6], m[1], m[4], m[7], m[2], m[5], m[8]);
	}

	// Unary operators

	// +=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator+=(U scalar) {
		column[0] += scalar;
		column[1] += scalar;
		column[2] += scalar;
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator+=(const tmat3<U> & other) {
		column[0] += other.column[0];
		column[1] += other.column[1];
		column[2] += other.column[2];
		return *this;
	}

	// -=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator-=(U scalar) {
		column[0] -= scalar;
		column[1] -= scalar;
		column[2] -= scalar;
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator-=(const tmat3<U> & other) {
		column[0] -= other.column[0];
		column[1] -= other.column[1];
		column[2] -= other.column[2];
		return *this;
	}

	// *=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator*=(U scalar) {
		column[0] *= scalar;
		column[1] *= scalar;
		column[2] *= scalar;
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC tmat3<T> & tmat3<T>::operator*=(const tmat3<U> & other) {
		return (*this = *this * other);
	}

	// /=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator/=(U scalar) {
		column[0] /= scalar;
		column[1] /= scalar;
		column[2] /= scalar;
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator/=(const tmat3<U> & other) {
		return *this *= other.inverse();
	}

	// Assign operator

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tmat3<T> & tmat3<T>::operator=(const tmat3<U> & other) {
		column[0] = other.column[0];
		column[1] = other.column[1];
		column[2] = other.column[2];
		return *this;
	}

	// Array Subscriptor

	template <typename T>
	CT_MATH_FUNC_INL T & tmat3<T>::operator[](const u32 & index) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 9, "ct::tmat3<T>: Can not access element at index %d", index);
		return m[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL const T & tmat3<T>::operator[](const u32 & index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 9, "ct::tmat3<T>: Can not access element at index %d", index);
		return m[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL T & tmat3<T>::operator()(const u32 & index) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 9, "ct::tmat3<T>: Can not access element at index %d", index);
		return m[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL const T & tmat3<T>::operator()(const u32 & index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 9, "ct::tmat3<T>: Can not access element at index %d", index);
		return m[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL const T & tmat3<T>::operator()(const u32 & x, const u32 & y) const {
		__CT_MATH_ASSERT(x >= 0 && x < 3 && y >= 0 && y < 3,
		                 "ct::tmat3<T> Can not access element at position [%d, %d]",
		                 x,
		                 y);
		return m[y + x * 3];
	}

	template <typename T>
	CT_MATH_FUNC_INL T & tmat3<T>::operator()(const u32 & x, const u32 & y) {
		__CT_MATH_ASSERT(x >= 0 && x < 3 && y >= 0 && y < 3,
		                 "ct::tmat3<T>: Can not access element at position [%d, %d]",
		                 x,
		                 y);
		return m[y + x * 3];
	}

	// Unary operators

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator+(const tmat3<T> & mat) {
		return mat;
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator-(const tmat3<T> & mat) {
		return tmat3<T>(-mat.col(0), -mat.col(1), -mat.col(2));
	}

	// Binary operators

	// +

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator+(const tmat3<T> & mat, T scalar) {
		return tmat3<T>(mat.col(0) + scalar, mat.col(1) + scalar, mat.col(2) + scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator+(T scalar, const tmat3<T> & mat) {
		return tmat3<T>(scalar + mat.col(0), scalar + mat.col(1), scalar + mat.col(2));
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator+(const tmat3<T> & left, const tmat3<T> & right) {
		return tmat3<T>(
		    left.col(0) + right.col(0), left.col(1) + right.col(1), left.col(2) + right.col(2));
	}

	// -

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator-(const tmat3<T> & mat, T scalar) {
		return tmat3<T>(mat.col(0) - scalar, mat.col(1) - scalar, mat.col(2) - scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator-(T scalar, const tmat3<T> & mat) {
		return tmat3<T>(scalar - mat.col(0), scalar - mat.col(1), scalar - mat.col(2));
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator-(const tmat3<T> & left, const tmat3<T> & right) {
		return tmat3<T>(
		    left.col(0) - right.col(0), left.col(1) - right.col(1), left.col(2) - right.col(2));
	}

	// *

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator*(const tmat3<T> & mat, T scalar) {
		return tmat3<T>(mat.col(0) * scalar, mat.col(1) * scalar, mat.col(2) * scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator*(T scalar, const tmat3<T> & mat) {
		return tmat3<T>(scalar * mat.col(0), scalar * mat.col(1), scalar * mat.col(2));
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator*(const tmat3<T> & left, const tmat3<T> & right) {
		return tmat3<T>(
		    // 1st column
		    left[0] * right[0] + left[3] * right[1] + left[6] * right[2],
		    left[1] * right[0] + left[4] * right[1] + left[7] * right[2],
		    left[2] * right[0] + left[5] * right[1] + left[8] * right[2],
		    // 2nd column
		    left[0] * right[3] + left[3] * right[4] + left[6] * right[5],
		    left[1] * right[3] + left[4] * right[4] + left[7] * right[5],
		    left[2] * right[3] + left[5] * right[4] + left[8] * right[5],
		    // 3th column
		    left[0] * right[6] + left[3] * right[7] + left[6] * right[8],
		    left[1] * right[6] + left[4] * right[7] + left[7] * right[8],
		    left[2] * right[6] + left[5] * right[7] + left[8] * right[8]);
	}

	// vector multiplication

	template <typename T>
	CT_MATH_FUNC_INL typename tmat3<T>::column_type
	operator*(const tmat3<T> & mat, typename tmat3<T>::row_type const & row_vec) {
		return typename tmat3<T>::column_type(
		    mat(0) * row_vec.x + mat(3) * row_vec.y + mat(6) * row_vec.z,
		    mat(1) * row_vec.x + mat(4) * row_vec.y + mat(7) * row_vec.z,
		    mat(2) * row_vec.x + mat(5) * row_vec.y + mat(8) * row_vec.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL typename tmat3<T>::row_type
	operator*(typename tmat3<T>::column_type const & col_vec, const tmat3<T> & mat) {
		return typename tmat3<T>::row_type(
		    mat(0) * col_vec.x + mat(1) * col_vec.y + mat(2) * col_vec.z,
		    mat(3) * col_vec.x + mat(4) * col_vec.y + mat(5) * col_vec.z,
		    mat(6) * col_vec.x + mat(7) * col_vec.y + mat(8) * col_vec.z);
	}

	// /

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator/(const tmat3<T> & mat, T scalar) {
		return tmat3<T>(mat.col(0) / scalar, mat.col(1) / scalar, mat.col(2) / scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator/(T scalar, const tmat3<T> & mat) {
		return tmat3<T>(scalar / mat.col(0), scalar / mat.col(1), scalar / mat.col(2));
	}

	template <typename T>
	CT_MATH_FUNC_INL tmat3<T> operator/(const tmat3<T> & left, const tmat3<T> & right) {
		return left * right.inverse();
	}

	// Boolean operators

	template <typename T>
	CT_MATH_FUNC bool operator==(const tmat3<T> & left, const tmat3<T> & right) {
		return (left.col(0) == right.col(0)) && (left.col(1) == right.col(1)) &&
		       (left.col(2) == right.col(2));
	}

	template <typename T>
	CT_MATH_FUNC bool operator!=(const tmat3<T> & left, const tmat3<T> & right) {
		return (left.col(0) != right.col(0)) || (left.col(1) != right.col(1)) ||
		       (left.col(2) != right.col(2));
	}

} // namespace ct
