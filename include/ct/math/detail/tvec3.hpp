
#ifndef _CHRONOTRIX_FRWK_MATH_TVEC3_HPP_
#define _CHRONOTRIX_FRWK_MATH_TVEC3_HPP_

#include <ct/math/detail/setup.hpp>
#include <ct/core/types/type_info.hpp>

namespace ct {

	template <typename T>
	struct tvec3 {
		using value_type = T;

		T x;
		T y;
		T z;

		// Default constructors

		CT_MATH_FUNC tvec3();
		CT_MATH_FUNC tvec3(const tvec3<T> & other) = default;

		// Explicit constructors

		CT_MATH_FUNC tvec3(T x, T y, T z);
		CT_MATH_FUNC explicit tvec3(T scalar);

		// Conversion constructors

		////////////////////////////////////////////////////////////
		/// @brief Conversion constructor from vector of 3 elements
		/// with different types.
		///
		/// @param vec3 Vector of 3 elements
		////////////////////////////////////////////////////////////
		template <typename U>
		CT_MATH_FUNC tvec3(const tvec3<U> & vec3);

		////////////////////////////////////////////////////////////
		/// @brief Conversion constructor from 3 elements
		/// of different types.
		///
		/// @param x X value
		/// @param y Y value
		/// @param z Z value
		////////////////////////////////////////////////////////////
		template <typename X, typename Y, typename Z>
		CT_MATH_FUNC tvec3(X x, Y y, Z z);

		////////////////////////////////////////////////////////////
		/// @brief Constructs from vector of 2 elements.
		/// z will be zeroed.
		///
		/// @param vec2 Vector of two elements
		////////////////////////////////////////////////////////////
		CT_MATH_FUNC tvec3(const tvec2<T> & vec2);

		////////////////////////////////////////////////////////////
		/// @brief Constructs from vector of 2 elements
		/// with z value.
		///
		/// @param vec2 Vector of two elements
		////////////////////////////////////////////////////////////
		CT_MATH_FUNC tvec3(const tvec2<T> & vec2, T z);

		template <typename U>
		CT_MATH_FUNC tvec3(const tvec2<U> & vec2);

		template <typename U, typename Z>
		CT_MATH_FUNC tvec3(const tvec2<U> & vec2, Z z);

		// Assign operators

		CT_MATH_FUNC tvec3<T> & operator=(const tvec3<T> & other) = default;

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator=(const tvec3<U> & other);

		// Unary operators

		// +=

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator+=(U scalar);

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator+=(const tvec3<U> & other);

		// -=

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator-=(U scalar);

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator-=(const tvec3<U> & other);

		// *=

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator*=(U scalar);

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator*=(const tvec3<U> & other);

		// /=

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator/=(U scalar);

		template <typename U>
		CT_MATH_FUNC tvec3<T> & operator/=(const tvec3<U> & other);

		// Relational operators

		CT_MATH_FUNC bool operator<(const tvec3<T> & other) const;
		CT_MATH_FUNC bool operator<=(const tvec3<T> & other) const;
		CT_MATH_FUNC bool operator>(const tvec3<T> & other) const;
		CT_MATH_FUNC bool operator>=(const tvec3<T> & other) const;

		// Array Subscriptor

		CT_MATH_FUNC T & operator[](const u32 & index);
		CT_MATH_FUNC const T & operator[](const u32 & index) const;
	};

	// Unary operators

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator+(const tvec3<T> & vec);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator-(const tvec3<T> & vec);

	// Binary operators

	// +

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator+(const tvec3<T> & other, T scalar);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator+(T scalar, const tvec3<T> & other);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator+(const tvec3<T> & left, const tvec3<T> & right);

	// -

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator-(const tvec3<T> & other, T scalar);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator-(T scalar, const tvec3<T> & other);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator-(const tvec3<T> & left, const tvec3<T> & right);

	// *

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator*(const tvec3<T> & other, T scalar);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator*(T scalar, const tvec3<T> & other);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator*(const tvec3<T> & left, const tvec3<T> & right);

	// /

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator/(const tvec3<T> & other, T scalar);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator/(T scalar, const tvec3<T> & other);

	template <typename T>
	CT_MATH_FUNC tvec3<T> operator/(const tvec3<T> & left, const tvec3<T> & right);

	// Boolean operators

	template <typename T>
	CT_MATH_FUNC bool operator==(const tvec3<T> & left, const tvec3<T> & right);

	template <typename T>
	CT_MATH_FUNC bool operator!=(const tvec3<T> & left, const tvec3<T> & right);

	// Vector of booleans operators only

	CT_MATH_FUNC tvec3<bool> operator&&(const tvec3<bool> & left, const tvec3<bool> & right);

	CT_MATH_FUNC tvec3<bool> operator||(const tvec3<bool> & left, const tvec3<bool> & right);

	// ostream operator

	template <typename T>
	std::ostream & operator<<(std::ostream & s, const tvec3<T> & v);

} // namespace ct

#include <ct/math/detail/tvec3.inl>

#endif
