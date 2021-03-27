
namespace ct {

	template <typename T>
	CONSTEXPR trect<T>::trect()
	:
	x(0),
	y(0),
	width(0),
	height(0)
	{}

	template <typename T>
	CONSTEXPR trect<T>::trect(T _x, T _y, T _width, T _height)
	:
	x(_x),
	y(_y),
	width(_width),
	height(_height)
	{}


	template <typename T>
	CONSTEXPR trect<T>::trect(const tvec2<T> & _position, const tvec2<T> & _size)
	:
	position(_position),
	size(_size)
	{}

	// Functions

	template <typename T>
	CONSTEXPR tvec2<T> trect<T>::top_left() const {
		return tvec2<T>(x, y);
	}

	template <typename T>
	CONSTEXPR tvec2<T> trect<T>::bottom_right() const {
		return tvec2<T>(x + width, y + height);
	}

	template <typename T>
	CONSTEXPR tvec2<T> trect<T>::center() const {
		return tvec2<T>(x + width / 2, y + height / 2);
	}

	template <typename T>
	CONSTEXPR bool trect<T>::intersects(const trect<T> & other) const {
		if (width <= 0 && height <= 0)
			return false;

		return (size > other.position && position < other.size) || (position > other.size && size < other.position);
	}

	template <typename T>
	CONSTEXPR bool trect<T>::contains(const tvec2<T> & point) const {
		if (width <= 0 && height <= 0)
			return false;

		return
			(point.x > x &&
			point.x < x + width &&
			point.y >= y &&
			point.y < y + height);
	}

	// Assign operators

	template <typename T>
	CONSTEXPR trect<T> & trect<T>::operator=(const trect<T> & other) {
		this->x = other.x;
		this->y = other.y;
		this->width = other.width;
		this->height = other.height;
		return *this;
	}

	template <typename T>
	template <typename U>
	CONSTEXPR trect<T> & trect<T>::operator=(const trect<U> & other) {
		this->x = static_cast<T>(other.x);
		this->y = static_cast<T>(other.y);
		this->width = static_cast<T>(other.width);
		this->height = static_cast<T>(other.height);
		return *this;
	}


	// Array Subscriptor

	template <typename T>
	CT_FORCEINLINE CONSTEXPR T & trect<T>::operator[](const u32 & index) {
		__CT_MATH_ASSERT(index >= 0 && index < 4, "ct::trect<T>: Can not access element with index %d", index);
		return (&x)[index];
	}

	template <typename T>
	CT_FORCEINLINE CONSTEXPR const T & trect<T>::operator[](const u32 & index) const {
		__CT_MATH_ASSERT(index >= 0 && index < 4, "ct::trect<T>: Can not access element with index %d", index);
		return (&x)[index];
	}

	template <typename T>
	std::ostream& operator<<(std::ostream &stream, const trect<T> &rect) {
		return stream << "ct::rect<" << type<T>::name << ">(" << rect.x << ", " << rect.y << ", "
		              << rect.width << ", " << rect.height << ')';
	}

}
