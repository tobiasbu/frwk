
#ifndef _CHRONOTRIX_FRWK_MATH_VEC2_HPP_
#define _CHRONOTRIX_FRWK_MATH_VEC2_HPP_

#include <ct/math/detail/setup.hpp>
#include <ct/core/utils/type_info.hpp>

namespace ct {
	namespace detail {

		template <typename T>
		struct vec2 {
			using value_type = T;

			T x, y;

			// Default constructors

			CONSTEXPR vec2();
			CONSTEXPR vec2(const vec2<T> & other) = default;

			// Explicit constructors

			CONSTEXPR vec2(T x, T y);
			CONSTEXPR explicit vec2(T scalar);

			// Conversion constructors

			template <typename X, typename Y>
			CONSTEXPR vec2(X x, Y y);

			template <typename U>
			CONSTEXPR vec2(const vec2<U> & v2);

			template <typename U>
			CONSTEXPR vec2(const vec3<U> & v3);

			template <typename U>
			CONSTEXPR vec2(const vec4<U> & v4);

			// Assign operators

			CONSTEXPR vec2<T> & operator=(const vec2 & other) = default;

			template <typename U>
			CONSTEXPR vec2<T> & operator=(const vec2<U> & other);

			// Unary operators

			// +=

			template <typename U>
			CONSTEXPR vec2<T> & operator+=(U scalar);

			template <typename U>
			CONSTEXPR vec2<T> & operator+=(const vec2<U> & other);

			// -=

			template <typename U>
			CONSTEXPR vec2<T> & operator-=(U scalar);

			template <typename U>
			CONSTEXPR vec2<T> & operator-=(const vec2<U> & other);

			// *=

			template <typename U>
			CONSTEXPR vec2<T> & operator*=(U scalar);

			template <typename U>
			CONSTEXPR vec2<T> & operator*=(const vec2<U> & other);

			// /=

			template <typename U>
			CONSTEXPR vec2<T> & operator/=(U scalar);

			template <typename U>
			CONSTEXPR vec2<T> & operator/=(const vec2<U> & other);

			// Array Subscriptor

			CONSTEXPR T & operator[](const u32 & index);
			CONSTEXPR const T & operator[](const u32 & index) const;
		};


		// Unary operators

		template <typename T>
		CONSTEXPR vec2<T> operator+(const vec2<T> & vec);

		template <typename T>
		CONSTEXPR vec2<T> operator-(const vec2<T> & vec);

		// Binary operators

		// +

		template <typename T>
		CONSTEXPR vec2<T> operator+(const vec2<T> & other, T scalar);

		template <typename T>
		CONSTEXPR vec2<T> operator+(T scalar, const vec2<T> & other);

		template <typename T>
		CONSTEXPR vec2<T> operator+(const vec2<T> & left, const vec2<T> & right);

		// -

		template <typename T>
		CONSTEXPR vec2<T> operator-(const vec2<T> & other, T scalar);

		template <typename T>
		CONSTEXPR vec2<T> operator-(T scalar, const vec2<T> & other);

		template <typename T>
		CONSTEXPR vec2<T> operator-(const vec2<T> & left, const vec2<T> & right);

		// *

		template <typename T>
		CONSTEXPR vec2<T> operator*(const vec2<T> & other, T scalar);

		template <typename T>
		CONSTEXPR vec2<T> operator*(T scalar, const vec2<T> & other);

		template <typename T>
		CONSTEXPR vec2<T> operator*(const vec2<T> & left, const vec2<T> & right);

		// /

		template <typename T>
		CONSTEXPR vec2<T> operator/(const vec2<T> & other, T scalar);

		template <typename T>
		CONSTEXPR vec2<T> operator/(T scalar, const vec2<T> & other);

		template <typename T>
		CONSTEXPR vec2<T> operator/(const vec2<T> & left, const vec2<T> & right);

		// Boolean operators

		template <typename T>
		CONSTEXPR bool operator==(const vec2<T> & left, const vec2<T> & right);

		template <typename T>
		CONSTEXPR bool operator!=(const vec2<T> & left, const vec2<T> & right);

		CONSTEXPR vec2<bool> operator&&(const vec2<bool> & left, const vec2<bool> & right);

		CONSTEXPR vec2<bool> operator||(const vec2<bool> & left, const vec2<bool> & right);

	} // namespace detail

} // namespace ct

#include <ct/math/detail/tml_vec2.inl>

#endif
