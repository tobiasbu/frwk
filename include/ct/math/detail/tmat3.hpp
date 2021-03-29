
#ifndef _CHRONOTRIX_FRWK_MATH_TMAT3_HPP_
#define _CHRONOTRIX_FRWK_MATH_TMAT3_HPP_

#include <ct/math/detail/tvec3.hpp>

namespace ct {

	////////////////////////////////////////////////////////////
	/// @brief Matrix 3x3 components
	///
	/// The matrices in Chronotrix are COLUMN-major order.
	/// Data access is defined as: `row + (column*3)`
	/// Column = x
	/// Row = y
	///
	/// @tparam T Value type
	////////////////////////////////////////////////////////////
	template <typename T>
	struct tmat3 {

		using value_type = T;
		using row_type = tvec3<T>;
		using column_type = tvec3<T>;

	private:

		union
		{
			T m[9];
			column_type column[3];
		};



	public:

		// Default constructors

		CONSTEXPR tmat3();
		CONSTEXPR tmat3(const tmat3<T> & other);

		// Explict constructors

		CONSTEXPR explicit tmat3(T identity);

		////////////////////////////////////////////////////////////
		/// @brief Explict Contructor
		///
		/// @param m00 x1 - [0,0] - 1th column | 1th row
		/// @param m10 y1 - [1,0] - 1th column | 2nd row
		/// @param m20 z1 - [2,0] - 1th column | 3rd row
		/// @param m01 x2 - [0,1] - 2nd column | 1th row
		/// @param m11 y2 - [1,1] - 2nd column | 2nd row
		/// @param m21 z2 - [2,1] - 2nd column | 3rd row
		/// @param m02 x3 - [0,2] - 3rd column | 1th row
		/// @param m12 y3 - [1,2] - 3rd column | 2nd row
		/// @param m22 z3 - [2,2] - 3rd column | 3rd row
		////////////////////////////////////////////////////////////
		CONSTEXPR tmat3(
			T m00, T m10, T m20,
			T m01, T m11, T m21,
			T m02, T m12, T m22);

		CONSTEXPR tmat3(
			const column_type & col_0,
			const column_type & col_1,
			const column_type & col_2);

		// Coversions constructors

		template <typename M00, typename M10, typename M20,
				  typename M01, typename M11, typename M21,
				  typename M02, typename M12, typename M22>
		CONSTEXPR tmat3(
			M00 m00, M10 m10, M20 m20,
			M01 m01, M11 m11, M21 m21,
			M02 m02, M12 m12, M22 m22);

		template <typename X, typename Y, typename Z>
		CONSTEXPR tmat3(
			const tvec3<X> & col_0,
			const tvec3<Y> & col_1,
			const tvec3<Z> & col_2);

		// Functions

		CONSTEXPR column_type get_column(u32 index) const;
		CONSTEXPR row_type get_row(u32 index) const;

		CONSTEXPR void set(T m00, T m10, T m20, T m01, T m11, T m21, T m02, T m12, T m22);
		CONSTEXPR void set_column(u32 index, const column_type & column);
		CONSTEXPR void set_row(u32 index, const row_type & row);

		CONSTEXPR T determinant() const;
		CONSTEXPR tmat3<T> inverse() const;
		CONSTEXPR void transpose();

		// Assign operators

		template <typename U>
		CONSTEXPR tmat3<T> & operator=(const tmat3<U> & other);

		// Unary operators

		// +=

		template <typename U>
		CONSTEXPR tmat3<T> & operator+=(U scalar);

		template <typename U>
		CONSTEXPR tmat3<T> & operator+=(const tmat3<U> & other);

		// -=

		template <typename U>
		CONSTEXPR tmat3<T> & operator-=(U scalar);

		template <typename U>
		CONSTEXPR tmat3<T> & operator-=(const tmat3<U> & other);

		// *=

		template <typename U>
		CONSTEXPR tmat3<T> & operator*=(U scalar);

		template <typename U>
		CONSTEXPR tmat3<T> & operator*=(const tmat3<U> & other);

		// /=

		template <typename U>
		CONSTEXPR tmat3<T> & operator/=(U scalar);

		template <typename U>
		CONSTEXPR tmat3<T> & operator/=(const tmat3<U> & other);

		// Array Subscriptor

		CONSTEXPR column_type & operator[](const u32 & index);
		CONSTEXPR const column_type & operator[](const u32 & index) const;

		////////////////////////////////////////////////////////////
		/// @brief Access to matrix column by given index
		///
		/// @param index row index
		////////////////////////////////////////////////////////////
		CONSTEXPR T & operator()(const u32 & index);

		////////////////////////////////////////////////////////////
		/// @brief Access to matrix column by given index
		///
		/// @param index column index
		////////////////////////////////////////////////////////////
		CONSTEXPR const T & operator()(const u32 & index) const;

		////////////////////////////////////////////////////////////
		/// @brief Access to element at [x, y]
		/// Row-major order access (`column + (row*3)`)
		///
		/// @param x row index
		/// @param y column index
		////////////////////////////////////////////////////////////
		CONSTEXPR T & operator()(const u32 & x, const u32 & y);

		////////////////////////////////////////////////////////////
		/// @brief Access to element at [x, y]
		/// Row-major order access (`column + (row*3)`)
		///
		/// @param x row index
		/// @param y column index
		////////////////////////////////////////////////////////////
		CONSTEXPR const T & operator()(const u32 & x, const u32 & y) const;

	};

	// Unary operators

	template <typename T>
	CONSTEXPR tmat3<T> operator+(const tmat3<T> & mat);

	template <typename T>
	CONSTEXPR tmat3<T> operator-(const tmat3<T> & mat);

	// Binary operators

	// +

	template <typename T>
	CONSTEXPR tmat3<T> operator+(const tmat3<T> & other, T scalar);

	template <typename T>
	CONSTEXPR tmat3<T> operator+(T scalar, const tmat3<T> & other);

	template <typename T>
	CONSTEXPR tmat3<T> operator+(const tmat3<T> & left, const tmat3<T> & right);

	// -

	template <typename T>
	CONSTEXPR tmat3<T> operator-(const tmat3<T> & other, T scalar);

	template <typename T>
	CONSTEXPR tmat3<T> operator-(T scalar, const tmat3<T> & other);

	template <typename T>
	CONSTEXPR tmat3<T> operator-(const tmat3<T> & left, const tmat3<T> & right);

	// *

	template <typename T>
	CONSTEXPR tmat3<T> operator*(const tmat3<T> & other, T scalar);

	template <typename T>
	CONSTEXPR tmat3<T> operator*(T scalar, const tmat3<T> & other);

	template <typename T>
	CONSTEXPR tmat3<T> operator*(const tmat3<T> & left, const tmat3<T> & right);

	// vector multiplication

	template <typename T>
	CONSTEXPR typename tmat3<T>::column_type operator*(const tmat3<T> & mat, typename const tmat3<T>::row_type & row_vec);

	template <typename T>
	CONSTEXPR typename tmat3<T>::row_type operator*(typename const tmat3<T>::column_type & col_vec, const tmat3<T> & mat);

	// /

	template <typename T>
	CONSTEXPR tmat3<T> operator/(const tmat3<T> & other, T scalar);

	template <typename T>
	CONSTEXPR tmat3<T> operator/(T scalar, const tmat3<T> & other);

	////////////////////////////////////////////////////////////
	/// @brief Divide matrix 'left' by matrix 'right'
	///
	/// Note: There is no such thing as Matrix 'division'.
	/// What exactly this operator do is inverse right matrix
    /// and then multiply left by right matrices.
	///
	/// Mathematically speaking it would be:
	/// [A]÷[B] = [A]*[B]^-1
	///
	/// @tparam T
	/// @param left
	/// @param right
	////////////////////////////////////////////////////////////
	template <typename T>
	CONSTEXPR tmat3<T> operator/(const tmat3<T> & left, const tmat3<T> & right);

	// Boolean operators

	template <typename T>
	CONSTEXPR bool operator==(const tmat3<T> & left, const tmat3<T> & right);

	template <typename T>
	CONSTEXPR bool operator!=(const tmat3<T> & left, const tmat3<T> & right);



}

#include <ct/math/detail/tmat3.inl>

#endif
