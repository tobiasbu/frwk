
#ifndef _CHRONOTRIX_FRWK_MATH_TRECT_HPP_
#define _CHRONOTRIX_FRWK_MATH_TRECT_HPP_

#include <ct/math/detail/tvec2.hpp>

namespace ct {

	template <typename T>
	struct trect {
		using value_type = T;

		union {
			tvec2<T> position;
			struct {
				T x;
				T y;
			};
		};

		union {
			tvec2<T> size;
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
		CONSTEXPR trect(const tvec2<T> & position, const tvec2<T> & size);

		// Functions

		CONSTEXPR tvec2<T> min(void) const;
		CONSTEXPR tvec2<T> max(void) const;

		CONSTEXPR tvec2<T> center() const;
		CONSTEXPR bool contains(const tvec2<T> & point) const;
		CONSTEXPR bool intersects(const trect<T> & other) const;

		// Assign operators

		CONSTEXPR tvec2<T> & operator=(const trect<T> & other);

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
