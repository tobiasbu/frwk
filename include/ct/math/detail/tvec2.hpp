
#ifndef _CHRONOTRIX_FRWK_MATH_TVEC2_HPP_
#define _CHRONOTRIX_FRWK_MATH_TVEC2_HPP_

#include <ostream>
#include <ct/math/detail/setup.hpp>
#include <ct/core/utils/type_info.hpp>

namespace ct {

	template <typename T>
	struct tvec2 {
		using value_type = T;

		T x;
		T y;

		// Default constructors

		CT_CONSTEXPR tvec2();
		CT_CONSTEXPR tvec2(const tvec2<T> & other) = default;

		// Explicit constructors

		CT_CONSTEXPR tvec2(T x, T y);
		CT_CONSTEXPR explicit tvec2(T scalar);

		// Conversion constructors

		template <typename X, typename Y>
		CT_CONSTEXPR tvec2(X x, Y y);

		template <typename U>
		CT_CONSTEXPR tvec2(const tvec2<U> & v2);

		// template <typename U>
		// CT_CONSTEXPR tvec2(const vec3<U> & v3);

		// template <typename U>
		// CT_CONSTEXPR tvec2(const vec4<U> & v4);

		// Assign operators

		CT_CONSTEXPR tvec2<T> & operator=(const tvec2<T> & other) = default;

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator=(const tvec2<U> & other);

		// Unary operators

		// +=

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator+=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator+=(const tvec2<U> & other);

		// -=

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator-=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator-=(const tvec2<U> & other);

		// *=

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator*=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator*=(const tvec2<U> & other);

		// /=

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator/=(U scalar);

		template <typename U>
		CT_CONSTEXPR tvec2<T> & operator/=(const tvec2<U> & other);

		// Relational operators

		CT_CONSTEXPR bool operator<(const tvec2<T> & other) const;
		CT_CONSTEXPR bool operator<=(const tvec2<T> & other) const;
		CT_CONSTEXPR bool operator>(const tvec2<T> & other) const;
		CT_CONSTEXPR bool operator>=(const tvec2<T> & other) const;

		// Array Subscriptor

		CT_CONSTEXPR T & operator[](const u32 & index);
		CT_CONSTEXPR const T & operator[](const u32 & index) const;

	};


	// Unary operators

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator+(const tvec2<T> & vec);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator-(const tvec2<T> & vec);

	// Binary operators

	// +

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator+(const tvec2<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator+(T scalar, const tvec2<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator+(const tvec2<T> & left, const tvec2<T> & right);

	// -

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator-(const tvec2<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator-(T scalar, const tvec2<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator-(const tvec2<T> & left, const tvec2<T> & right);

	// *

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator*(const tvec2<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator*(T scalar, const tvec2<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator*(const tvec2<T> & left, const tvec2<T> & right);

	// /

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator/(const tvec2<T> & other, T scalar);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator/(T scalar, const tvec2<T> & other);

	template <typename T>
	CT_CONSTEXPR tvec2<T> operator/(const tvec2<T> & left, const tvec2<T> & right);

	// Boolean operators

	template <typename T>
	CT_CONSTEXPR bool operator==(const tvec2<T> & left, const tvec2<T> & right);

	template <typename T>
	CT_CONSTEXPR bool operator!=(const tvec2<T> & left, const tvec2<T> & right);

	// Vector of booleans operators only

	CT_CONSTEXPR tvec2<bool> operator&&(const tvec2<bool> & left, const tvec2<bool> & right);

	CT_CONSTEXPR tvec2<bool> operator||(const tvec2<bool> & left, const tvec2<bool> & right);

	// ostream operator

	template <typename T>
	std::ostream& operator<<(std::ostream &s, const tvec2<T> &v);

} // namespace ct

#include <ct/math/detail/tvec2.inl>

#endif
