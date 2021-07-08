
#ifndef _CHRONOTRIX_FRWK_MATH_TVEC4_HPP_
#define _CHRONOTRIX_FRWK_MATH_TVEC4_HPP_

#include <ct/math/detail/setup.hpp>
#include <ct/core/utils/type_info.hpp>

namespace ct {

	template <typename T>
	struct tvec4 {
		using value_type = T;

		T x;
		T y;
		T z;
		T w;

		// Default constructors

		CT_CONSTEXPR tvec4();
		CT_CONSTEXPR tvec4(const tvec4<T> & other) = default;

		// Explicit constructors

		CT_CONSTEXPR explicit tvec4(T scalar);
		CT_CONSTEXPR tvec4(T x, T y, T z, T w);

		// Conversion constructors - scalar

		template <typename U>
		CT_CONSTEXPR tvec4(U scalar);

		////////////////////////////////////////////////////////////
		/// @brief Explicit conversion constructor from scalar elements
		///
		/// @param x X value
		/// @param y Y value
		/// @param z Z value
		/// @param w W value
		////////////////////////////////////////////////////////////
		template <typename X, typename Y, typename Z, typename W>
		CT_CONSTEXPR tvec4(X x, Y y, Z z, W w);

		// Conversion constructors - vec2

		////////////////////////////////////////////////////////////
		/// @brief Constructs from two vectors of 2 elements.
		///
		/// @param vec2_a First vector of 2 elements
		/// @param vec2_b Second vector of 2 elements
		////////////////////////////////////////////////////////////
		CT_CONSTEXPR tvec4(const tvec2<T> & vec2_a, const tvec2<T> & vec2_b);

		////////////////////////////////////////////////////////////
		/// @brief Constructs from two vectors of 2 elements.
		///
		/// @param vec2_a First vector of 2 elements
		/// @param vec2_b Second vector of 2 elements
		////////////////////////////////////////////////////////////
		template <typename XY, typename ZW>
		CT_CONSTEXPR tvec4(const tvec2<XY> & xy, const tvec2<ZW> & zw);

		// Conversion constructors - vec3

		////////////////////////////////////////////////////////////
		/// @brief Constructs from vector of 3 elements.
		/// w will be zeroed.
		///
		/// @param vec2 Vector of 3 elements
		////////////////////////////////////////////////////////////
		CT_CONSTEXPR tvec4(const tvec3<T> & vec3);

		////////////////////////////////////////////////////////////
		/// @brief Constructs from vector of 3 elements with w value.
		///
		/// @param vec2 Vector of two elements
		////////////////////////////////////////////////////////////
		CT_CONSTEXPR tvec4(const tvec3<T> & vec3, T w);

		template <typename U>
		CT_CONSTEXPR tvec4(const tvec3<U> & vec3);

		template <typename U, typename W>
		CT_CONSTEXPR tvec4(const tvec3<U> & vec3, W w);

		// Conversion constructors - vec4

		////////////////////////////////////////////////////////////
		/// @brief Explict conversion from vector of 4 elements of type U
		///
		/// @param vec4 Vector of 4 elements
		////////////////////////////////////////////////////////////
		template <typename U>
		CT_CONSTEXPR tvec4(const tvec4<U> & vec4);

		// Functions

		CT_CONSTEXPR void set(T x, T y, T z, T w);

		// Assign operators

		CT_CONSTEXPR tvec4<T> & operator=(const tvec4<T> & other) = default;

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator=(const tvec4<U> & other);

		// Unary operators

		// +=

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator+=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator+=(const tvec4<U> & other);

		// -=

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator-=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator-=(const tvec4<U> & other);

		// *=

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator*=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator*=(const tvec4<U> & other);

		// /=

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator/=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec4<T> & operator/=(const tvec4<U> & other);

		// Relational operators

		CT_CONSTEXPR bool operator<(const tvec4<T> & other) const;
		CT_CONSTEXPR bool operator<=(const tvec4<T> & other) const;
		CT_CONSTEXPR bool operator>(const tvec4<T> & other) const;
		CT_CONSTEXPR bool operator>=(const tvec4<T> & other) const;

		// Array Subscriptor

		CT_CONSTEXPR T & operator[](const u32 & index);
		CT_CONSTEXPR const T & operator[](const u32 & index) const;

	};

	// Unary operators

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator+(const tvec4<T> & vec);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator-(const tvec4<T> & vec);

	// Binary operators

	// +

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator+(const tvec4<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator+(T scalar, const tvec4<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator+(const tvec4<T> & left, const tvec4<T> & right);

	// -

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator-(const tvec4<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator-(T scalar, const tvec4<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator-(const tvec4<T> & left, const tvec4<T> & right);

	// *

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator*(const tvec4<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator*(T scalar, const tvec4<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator*(const tvec4<T> & left, const tvec4<T> & right);

	// /

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator/(const tvec4<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator/(T scalar, const tvec4<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec4<T> operator/(const tvec4<T> & left, const tvec4<T> & right);

	// Boolean operators

	template <typename T>
	CT_CONSTEXPR bool operator==(const tvec4<T> & left, const tvec4<T> & right);

	template <typename T>
	CT_CONSTEXPR bool operator!=(const tvec4<T> & left, const tvec4<T> & right);

	// Vector of booleans operators only

	CT_CONSTEXPR tvec4<bool> operator&&(const tvec4<bool> & left, const tvec4<bool> & right);

	CT_CONSTEXPR tvec4<bool> operator||(const tvec4<bool> & left, const tvec4<bool> & right);

	// ostream operator

	template <typename T>
	std::ostream& operator<<(std::ostream &s, const tvec4<T> &v);

}

#include <ct/math/detail/tvec4.inl>

#endif
