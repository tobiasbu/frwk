
namespace ct {

	// Default constructos

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T>::tvec2() : x(static_cast<T>(0)),
	                                     y(static_cast<T>(0)) {}

	// Explicit constructors

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T>::tvec2(T _x, T _y) : x(_x),
	                                               y(_y) {}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T>::tvec2(T scalar) : x(scalar),
	                                             y(scalar) {}

	// Conversion constructors

	template <typename T>
	template <typename X, typename Y>
	CT_MATH_FUNC_INL tvec2<T>::tvec2(X _x, Y _y) : x(static_cast<T>(_x)),
	                                               y(static_cast<T>(_y)) {}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T>::tvec2(const tvec2<U> & v2)
	: x(static_cast<T>(v2.x)),
	  y(static_cast<T>(v2.y)) {}

	// template <typename T>
	// template <typename U>
	// CT_MATH_FUNC_INL tvec2<T>::tvec2(const vec3<U> & v3)
	// : x(static_cast<T>(v3.x)),
	// 	y(static_cast<T>(v3.y)) {}

	// template <typename T>
	// template <typename U>
	// CT_MATH_FUNC_INL tvec2<T>::tvec2(const vec4<U> & v4)
	// : x(static_cast<T>(v4.x)),
	// 	y(static_cast<T>(v4.y)) {}

	// Assign operators

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator=(const tvec2<U> & other) {
		this->x = static_cast<T>(other.x);
		this->y = static_cast<T>(other.y);
		return *this;
	};

	// Unary operators

	// +=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator+=(U scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator+=(const tvec2<U> & other) {
		this->x += static_cast<T>(other.x);
		this->y += static_cast<T>(other.y);
		return *this;
	}

	// -=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator-=(U scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator-=(const tvec2<U> & other) {
		this->x -= static_cast<T>(other.x);
		this->y -= static_cast<T>(other.y);
		return *this;
	}

	// *=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator*=(U scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator*=(const tvec2<U> & other) {
		this->x *= static_cast<T>(other.x);
		this->y *= static_cast<T>(other.y);
		return *this;
	}

	// /=
	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator/=(U scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec2<T> & tvec2<T>::operator/=(const tvec2<U> & other) {
		this->x /= static_cast<T>(other.x);
		this->y /= static_cast<T>(other.y);
		return *this;
	}

	// Relational operators

	template <typename T>
	CT_MATH_FUNC_INL bool tvec2<T>::operator<(const tvec2<T> & other) const {
		return (this->x < other.x) && (this->y < other.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec2<T>::operator<=(const tvec2<T> & other) const {
		return (this->x <= other.x) && (this->y <= other.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec2<T>::operator>(const tvec2<T> & other) const {
		return (this->x > other.x) && (this->y > other.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec2<T>::operator>=(const tvec2<T> & other) const {
		return (this->x >= other.x) && (this->y >= other.y);
	}

	// Array Subscriptor

	template <typename T>
	CT_MATH_FUNC_INL T & tvec2<T>::operator[](const u32 & index) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 2, "ct::tvec2<T>: Can not access element with index %d", index);
		return index ? y : x;
	}

	template <typename T>
	CT_MATH_FUNC_INL const T & tvec2<T>::operator[](const u32 & index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 2, "ct::tvec2<T>: Can not access element with index %d", index);
		return index ? y : x; // return (&x)[index];
	}

	// Unary operators

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator+(const tvec2<T> & vec) {
		return vec;
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator-(const tvec2<T> & vec) {
		return tvec2<T>(-vec.x, -vec.y);
	}

	// Binary operators

	// +

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator+(const tvec2<T> & other, T scalar) {
		return tvec2<T>(other.x + scalar, other.y + scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator+(T scalar, const tvec2<T> & other) {
		return tvec2<T>(scalar + other.x, scalar + other.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator+(const tvec2<T> & left, const tvec2<T> & right) {
		return tvec2<T>(left.x + right.x, left.y + right.y);
	}

	// -

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator-(const tvec2<T> & other, T scalar) {
		return tvec2<T>(other.x - scalar, other.y - scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator-(T scalar, const tvec2<T> & other) {
		return tvec2<T>(scalar - other.x, scalar - other.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator-(const tvec2<T> & left, const tvec2<T> & right) {
		return tvec2<T>(left.x - right.x, left.y - right.y);
	}

	// *

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator*(const tvec2<T> & other, T scalar) {
		return tvec2<T>(other.x * scalar, other.y * scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator*(T scalar, const tvec2<T> & other) {
		return tvec2<T>(scalar * other.x, scalar * other.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator*(const tvec2<T> & left, const tvec2<T> & right) {
		return tvec2<T>(left.x * right.x, left.y * right.y);
	}

	// /

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator/(const tvec2<T> & other, T scalar) {
		return tvec2<T>(other.x / scalar, other.y / scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator/(T scalar, const tvec2<T> & other) {
		return tvec2<T>(scalar / other.x, scalar / other.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec2<T> operator/(const tvec2<T> & left, const tvec2<T> & right) {
		return tvec2<T>(left.x / right.x, left.y / right.y);
	}

	// Boolean operators

	template <typename T>
	CT_MATH_FUNC_INL bool operator==(const tvec2<T> & left, const tvec2<T> & right) {
		return (left.x == right.x) && (left.y == right.y);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool operator!=(const tvec2<T> & left, const tvec2<T> & right) {
		return (left.x != right.x || left.y != right.y);
	}

	// Vector of booleans operators only

	CT_MATH_FUNC_INL tvec2<bool> operator&&(const tvec2<bool> & left, const tvec2<bool> & right) {
		return tvec2<bool>(left.x && right.x, left.y && right.y);
	}

	CT_MATH_FUNC_INL tvec2<bool> operator||(const tvec2<bool> & left, const tvec2<bool> & right) {
		return tvec2<bool>(left.x || right.x, left.y || right.y);
	}

	// ostream operator
	template <typename T>
	std::ostream & operator<<(std::ostream & s, const tvec2<T> & v) {
		return s << "ct::vec2<" << type<T>::name << ">(" << v.x << ", " << v.y << ')';
	}

} // namespace ct
