
#ifndef _CHRONOTRIX_FRWK_MATH_TMAT4_HPP_
#define _CHRONOTRIX_FRWK_MATH_TMAT4_HPP_

#include <ct/math/detail/setup.hpp>

namespace ct {

	template <typename T>
	struct tmat4 {

		using value_type = T;
		using row_type = tvec4<T>;
		using column_type = tvec4<T>;

		private:

		union
		{
			T m[16];
			column_type column[4];
		};

		public:

		// Default constructors

		CONSTEXPR tmat4();
		CONSTEXPR tmat4(const tmat4<T> & other);

		// Explicit constructors

		explicit CONSTEXPR tmat4(T identity);

		CONSTEXPR tmat4(
			T m00, T m10, T m20, T m30,
			T m01, T m11, T m21, T m31,
			T m02, T m12, T m22, T m32,
		    T m03, T m13, T m23, T m33);

		CONSTEXPR tmat4(
			const column_type & col_0,
			const column_type & col_1,
			const column_type & col_2,
			const column_type & col_3);

		// Coversions constructors

		template <typename M00, typename M10, typename M20, typename M30,
				  typename M01, typename M11, typename M21, typename M31,
				  typename M02, typename M12, typename M22, typename M32,
				  typename M03, typename M13, typename M23, typename M33>
		CONSTEXPR tmat4(
			M00 m00, M10 m10, M20 m20, M30 m30,
			M01 m01, M11 m11, M21 m21, M31 m31,
			M02 m02, M12 m12, M22 m22, M32 m32,
			M03 m03, M13 m13, M23 m23, M33 m33);

		// Functions

		CONSTEXPR const column_type & col(const u32 & index) const;
		CONSTEXPR column_type & col(const u32 & index);

		CONSTEXPR column_type get_column(u32 index) const;
		CONSTEXPR row_type get_row(u32 index) const;

		CONSTEXPR void set(T m00,T m10,T m20,T m30,
		                   T m01,T m11,T m21,T m31,
		                   T m02,T m12,T m22,T m32,
		                   T m03,T m13,T m23,T m33);
		CONSTEXPR void set_column(u32 index, const column_type & column);
		CONSTEXPR void set_row(u32 index, const row_type & row);

		CONSTEXPR T determinant() const;
		CONSTEXPR tmat4<T> inverse() const;
		CONSTEXPR void transpose();

		// Array Subscriptor

		CONSTEXPR T & operator[](const u32 & index);
		CONSTEXPR const T & operator[](const u32 & index) const;

		////////////////////////////////////////////////////////////
		/// @brief Get pointer to matrix data
		///
		////////////////////////////////////////////////////////////
		CONSTEXPR T * operator()();

		////////////////////////////////////////////////////////////
		/// @brief Get pointer to matrix data
		///
		////////////////////////////////////////////////////////////
		CONSTEXPR const T * operator()() const;

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
		/// Row-major order access like `column + (row*4)`
		///
		/// @param x row index
		/// @param y column index
		////////////////////////////////////////////////////////////
		CONSTEXPR T & operator()(const u32 & x, const u32 & y);

		////////////////////////////////////////////////////////////
		/// @brief Access to element at [x, y]
		/// Row-major order access like `column + (row*4)`
		///
		/// @param x row index
		/// @param y column index
		////////////////////////////////////////////////////////////
		CONSTEXPR const T & operator()(const u32 & x, const u32 & y) const;


	};

	// *

	template <typename T>
	CONSTEXPR tmat4<T> operator*(const tmat4<T> & mat, T scalar);


} // namespace ct

#include <ct/math/detail/tmat4.inl>

#endif
