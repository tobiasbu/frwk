
namespace ct {

	// Default constructors

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T>::tvec3()
	: x(static_cast<T>(0)),
	  y(static_cast<T>(0)),
	  z(static_cast<T>(0)) {}

	// Explicit constructors

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(T _x, T _y, T _z) : x(_x),
	                                                     y(_y),
	                                                     z(_z) {}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(T scalar) : x(scalar),
	                                             y(scalar),
	                                             z(scalar) {}

	// Conversion constructors

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(const tvec3<U> & vec3)
	: x(static_cast<T>(vec3.x)),
	  y(static_cast<T>(vec3.y)),
	  z(static_cast<T>(vec3.z)) {}

	template <typename T>
	template <typename X, typename Y, typename Z>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(X _x, Y _y, Z _z)
	: x(static_cast<T>(_x)),
	  y(static_cast<T>(_y)),
	  z(static_cast<T>(_z)) {}

	// Conversion constructors - from vec2

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(const tvec2<T> & vec2)
	: x(vec2.x),
	  y(vec2.y),
	  z(static_cast<T>(0)) {}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(const tvec2<T> & vec2, T _z) : x(vec2.x),
	                                                                y(vec2.y),
	                                                                z(_z) {}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(const tvec2<U> & vec2)
	: x(static_cast<T>(vec2.x)),
	  y(static_cast<T>(vec2.y)),
	  z(static_cast<T>(0)) {}

	template <typename T>
	template <typename U, typename Z>
	CT_MATH_FUNC_INL tvec3<T>::tvec3(const tvec2<U> & vec2, Z _z)
	: x(static_cast<T>(vec2.x)),
	  y(static_cast<T>(vec2.y)),
	  z(static_cast<T>(_z)) {}

	// Assign operators

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator=(const tvec3<U> & other) {
		this->x = static_cast<T>(other.x);
		this->y = static_cast<T>(other.y);
		this->z = static_cast<T>(other.z);
		return *this;
	}

	// Unary operators

	// +=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator+=(U scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator+=(const tvec3<U> & other) {
		this->x += static_cast<T>(other.x);
		this->y += static_cast<T>(other.y);
		this->z += static_cast<T>(other.z);
		return *this;
	}

	// -=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator-=(U scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator-=(const tvec3<U> & other) {
		this->x -= static_cast<T>(other.x);
		this->y -= static_cast<T>(other.y);
		this->z -= static_cast<T>(other.z);
		return *this;
	}

	// *=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator*=(U scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator*=(const tvec3<U> & other) {
		this->x *= static_cast<T>(other.x);
		this->y *= static_cast<T>(other.y);
		this->z *= static_cast<T>(other.z);
		return *this;
	}

	// /=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator/=(U scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec3<T> & tvec3<T>::operator/=(const tvec3<U> & other) {
		this->x /= static_cast<T>(other.x);
		this->y /= static_cast<T>(other.y);
		this->z /= static_cast<T>(other.z);
		return *this;
	}

	// Relational operators

	template <typename T>
	CT_MATH_FUNC_INL bool tvec3<T>::operator<(const tvec3<T> & other) const {
		return (this->x < other.x) && (this->y < other.y) && (this->z < other.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec3<T>::operator<=(const tvec3<T> & other) const {
		return (this->x <= other.x) && (this->y <= other.y) && (this->z <= other.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec3<T>::operator>(const tvec3<T> & other) const {
		return (this->x > other.x) && (this->y > other.y) && (this->z > other.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec3<T>::operator>=(const tvec3<T> & other) const {
		return (this->x >= other.x) && (this->y >= other.y) && (this->z >= other.z);
	}

	// Array Subscriptor

	template <typename T>
	CT_MATH_FUNC_INL T & tvec3<T>::operator[](const u32 & index) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 3, "ct::tvec3<T>: Can not access element with index %d", index);
		return (&x)[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL const T & tvec3<T>::operator[](const u32 & index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 3, "ct::tvec3<T>: Can not access element with index %d", index);
		return (&x)[index];
	}

	// Unary operators

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator+(const tvec3<T> & vec) {
		return vec;
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator-(const tvec3<T> & vec) {
		return tvec3<T>(-vec.x, -vec.y, -vec.z);
	}

	// Binary operators

	// +

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator+(const tvec3<T> & other, T scalar) {
		return tvec3<T>(other.x + scalar, other.y + scalar, other.z + scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator+(T scalar, const tvec3<T> & other) {
		return tvec3<T>(scalar + other.x, scalar + other.y, scalar + other.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator+(const tvec3<T> & left, const tvec3<T> & right) {
		return tvec3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	// -

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator-(const tvec3<T> & other, T scalar) {
		return tvec3<T>(other.x - scalar, other.y - scalar, other.z - scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator-(T scalar, const tvec3<T> & other) {
		return tvec3<T>(scalar - other.x, scalar - other.y, scalar - other.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator-(const tvec3<T> & left, const tvec3<T> & right) {
		return tvec3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	// *

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator*(const tvec3<T> & other, T scalar) {
		return tvec3<T>(other.x * scalar, other.y * scalar, other.z * scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator*(T scalar, const tvec3<T> & other) {
		return tvec3<T>(scalar * other.x, scalar * other.y, scalar * other.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator*(const tvec3<T> & left, const tvec3<T> & right) {
		return tvec3<T>(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	// /

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator/(const tvec3<T> & other, T scalar) {
		return tvec3<T>(other.x / scalar, other.y / scalar, other.z / scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator/(T scalar, const tvec3<T> & other) {
		return tvec3<T>(scalar / other.x, scalar / other.y, scalar / other.z);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec3<T> operator/(const tvec3<T> & left, const tvec3<T> & right) {
		return tvec3<T>(left.x / right.x, left.y / right.y, left.z / right.z);
	}

	// Boolean operators

	template <typename T>
	CT_MATH_FUNC_INL bool operator==(const tvec3<T> & left, const tvec3<T> & right) {
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	template <typename T>
	CT_MATH_FUNC_INL bool operator!=(const tvec3<T> & left, const tvec3<T> & right) {
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
	}

	// Vector of booleans operators only

	CT_MATH_FUNC_INL tvec3<bool> operator&&(const tvec3<bool> & left, const tvec3<bool> & right) {
		return tvec3<bool>(left.x && right.x, left.y && right.y, left.z && right.z);
	}

	CT_MATH_FUNC_INL tvec3<bool> operator||(const tvec3<bool> & left, const tvec3<bool> & right) {
		return tvec3<bool>(left.x || right.x, left.y || right.y, left.z || right.z);
	}

	// ostream operator
	template <typename T>
	std::ostream & operator<<(std::ostream & s, const tvec3<T> & v) {
		return s << "ct::vec3<" << type<T>::name << ">(" << v.x << ", " << v.y << ", " << v.z
		         << ')';
	}

} // namespace ct
