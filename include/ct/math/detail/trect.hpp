
#ifndef _CHRONOTRIX_FRWK_MATH_TRECT_HPP_
#define _CHRONOTRIX_FRWK_MATH_TRECT_HPP_

#include <ct/math/detail/tvec2.hpp>

namespace ct {

	template <typename T>
	struct trect {
		using value_type = T;
		using point_type = tvec2<T>;

		union {
			point_type position;
			struct {
				T x;
				T y;
			};
		};

		union {
			point_type size;
			struct {
				T width;
				T height;
			};
		};

		// Default constructors

		CONSTEXPR trect();
		CONSTEXPR trect(const trect<T> & other) = default;
		CONSTEXPR trect(trect<T> && other) = default;

		CONSTEXPR trect(T x, T y, T width, T height);
		CONSTEXPR trect(const point_type & position, const point_type & size);

		// Functions

		CONSTEXPR point_type top_left() const;
		CONSTEXPR point_type bottom_right() const;

		CONSTEXPR point_type center() const;
		CONSTEXPR bool contains(const point_type & point) const;
		CONSTEXPR bool intersects(const trect<T> & other) const;

		// Assign operators

		CONSTEXPR trect<T> & operator=(const trect<T> & other);

		template <typename U>
		CONSTEXPR trect<T> & operator=(const trect<U> & other);

		// Array Subscriptor

		CONSTEXPR T & operator[](const u32 & index);
		CONSTEXPR const T & operator[](const u32 & index) const;

	};

	template <typename T>
	std::ostream& operator<<(std::ostream &stream, const trect<T> &rect);

}

#include <ct/math/detail/trect.inl>

#endif
