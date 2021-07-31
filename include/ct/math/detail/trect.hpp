
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

		CT_MATH_FUNC trect();
		CT_MATH_FUNC trect(const trect<T> & other) = default;
		CT_MATH_FUNC trect(trect<T> && other) = default;

		CT_MATH_FUNC trect(T x, T y, T width, T height);
		CT_MATH_FUNC trect(const point_type & position, const point_type & size);

		// Functions

		CT_MATH_FUNC point_type top_left() const;
		CT_MATH_FUNC point_type bottom_right() const;

		CT_MATH_FUNC point_type center() const;
		CT_MATH_FUNC bool contains(const point_type & point) const;
		CT_MATH_FUNC bool intersects(const trect<T> & other) const;

		// Assign operators

		CT_MATH_FUNC trect<T> & operator=(const trect<T> & other);

		template <typename U>
		CT_MATH_FUNC trect<T> & operator=(const trect<U> & other);

		// Array Subscriptor

		CT_MATH_FUNC T & operator[](const u32 & index);
		CT_MATH_FUNC const T & operator[](const u32 & index) const;
	};

	template <typename T>
	std::ostream & operator<<(std::ostream & stream, const trect<T> & rect);

} // namespace ct

#include <ct/math/detail/trect.inl>

#endif
