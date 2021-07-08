
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

		CT_CONSTEXPR trect();
		CT_CONSTEXPR trect(const trect<T> & other) = default;
		CT_CONSTEXPR trect(trect<T> && other) = default;

		CT_CONSTEXPR trect(T x, T y, T width, T height);
		CT_CONSTEXPR trect(const point_type & position, const point_type & size);

		// Functions

		CT_CONSTEXPR point_type top_left() const;
		CT_CONSTEXPR point_type bottom_right() const;

		CT_CONSTEXPR point_type center() const;
		CT_CONSTEXPR bool contains(const point_type & point) const;
		CT_CONSTEXPR bool intersects(const trect<T> & other) const;

		// Assign operators

		CT_CONSTEXPR trect<T> & operator=(const trect<T> & other);

		template <typename U>
		CT_CONSTEXPR trect<T> & operator=(const trect<U> & other);

		// Array Subscriptor

		CT_CONSTEXPR T & operator[](const u32 & index);
		CT_CONSTEXPR const T & operator[](const u32 & index) const;

	};

	template <typename T>
	std::ostream& operator<<(std::ostream &stream, const trect<T> &rect);

}

#include <ct/math/detail/trect.inl>

#endif
