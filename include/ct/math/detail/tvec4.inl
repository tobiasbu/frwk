
namespace ct {

	// Default constructors

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T>::tvec4() : x(0),
	                                     y(0),
	                                     z(0),
	                                     w(0) {}

	// Explicit constructors

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(T scalar) : x(scalar),
	                                             y(scalar),
	                                             z(scalar),
	                                             w(scalar) {}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(T _x, T _y, T _z, T _w) : x(_x),
	                                                           y(_y),
	                                                           z(_z),
	                                                           w(_w) {}

	// Conversion constructors - scalar

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(U scalar)
	: x(static_cast<T>(scalar)),
	  y(static_cast<T>(scalar)),
	  z(static_cast<T>(scalar)),
	  w(static_cast<T>(scalar)) {}

	template <typename T>
	template <typename X, typename Y, typename Z, typename W>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(X _x, Y _y, Z _z, W _w)
	: x(static_cast<T>(_x)),
	  y(static_cast<T>(_y)),
	  z(static_cast<T>(_z)),
	  w(static_cast<T>(_w)) {}

	// Conversion constructors - from vec2

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(const tvec2<T> & vec2_a, const tvec2<T> & vec2_b)
	: x(vec2_a.x),
	  y(vec2_a.y),
	  z(vec2_b.x),
	  w(vec2_b.y) {}

	template <typename T>
	template <typename XY, typename ZW>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(const tvec2<XY> & xy, const tvec2<ZW> & zw)
	: x(static_cast<T>(xy.x)),
	  y(static_cast<T>(xy.y)),
	  z(static_cast<T>(zw.x)),
	  w(static_cast<T>(zw.y)) {}

	// Conversion constructor - from vec3

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(const tvec3<T> & vec3)
	: x(vec3.x),
	  y(vec3.y),
	  z(vec3.z),
	  w(0) {}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(const tvec3<T> & vec3, T _w)
	: x(vec3.x),
	  y(vec3.y),
	  z(vec3.z),
	  w(_w) {}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(const tvec3<U> & vec3)
	: x(static_cast<T>(vec3.x)),
	  y(static_cast<T>(vec3.y)),
	  z(static_cast<T>(vec3.z)),
	  w(0) {}

	template <typename T>
	template <typename U, typename W>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(const tvec3<U> & vec3, W _w)
	: x(static_cast<T>(vec3.x)),
	  y(static_cast<T>(vec3.y)),
	  z(static_cast<T>(vec3.w)),
	  w(static_cast<T>(_w)) {}

	// Conversion constructor - from vec4

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T>::tvec4(const tvec4<U> & other)
	: x(static_cast<T>(other.x)),
	  y(static_cast<T>(other.y)),
	  z(static_cast<T>(other.z)),
	  w(static_cast<T>(other.w)) {}

	// Functions

	template <typename T>
	CT_MATH_FUNC_INL void tvec4<T>::set(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	// Assign operators

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator=(const tvec4<U> & other) {
		this->x = static_cast<T>(other.x);
		this->y = static_cast<T>(other.y);
		this->z = static_cast<T>(other.z);
		this->w = static_cast<T>(other.w);
		return *this;
	}

	// Unary operators

	// +=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator+=(U scalar) {
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		this->w += static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator+=(const tvec4<U> & other) {
		this->x += static_cast<T>(other.x);
		this->y += static_cast<T>(other.y);
		this->z += static_cast<T>(other.z);
		this->w += static_cast<T>(other.w);
		return *this;
	}

	// -=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator-=(U scalar) {
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		this->w -= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator-=(const tvec4<U> & other) {
		this->x -= static_cast<T>(other.x);
		this->y -= static_cast<T>(other.y);
		this->z -= static_cast<T>(other.z);
		this->w -= static_cast<T>(other.w);
		return *this;
	}

	// *=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator*=(U scalar) {
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		this->w *= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator*=(const tvec4<U> & other) {
		this->x *= static_cast<T>(other.x);
		this->y *= static_cast<T>(other.y);
		this->z *= static_cast<T>(other.z);
		this->w *= static_cast<T>(other.w);
		return *this;
	}

	// /=

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator/=(U scalar) {
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		this->z /= static_cast<T>(scalar);
		this->w /= static_cast<T>(scalar);
		return *this;
	}

	template <typename T>
	template <typename U>
	CT_MATH_FUNC_INL tvec4<T> & tvec4<T>::operator/=(const tvec4<U> & other) {
		this->x /= static_cast<T>(other.x);
		this->y /= static_cast<T>(other.y);
		this->z /= static_cast<T>(other.z);
		this->w /= static_cast<T>(other.w);
		return *this;
	}

	// Relational operators

	template <typename T>
	CT_MATH_FUNC_INL bool tvec4<T>::operator<(const tvec4<T> & other) const {
		return (this->x < other.x) && (this->y < other.y) && (this->z < other.z) &&
		       (this->w < other.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec4<T>::operator<=(const tvec4<T> & other) const {
		return (this->x <= other.x) && (this->y <= other.y) && (this->z <= other.z) &&
		       (this->w <= other.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec4<T>::operator>(const tvec4<T> & other) const {
		return (this->x > other.x) && (this->y > other.y) && (this->z > other.z) &&
		       (this->w > other.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool tvec4<T>::operator>=(const tvec4<T> & other) const {
		return (this->x >= other.x) && (this->y >= other.y) && (this->z >= other.z) &&
		       (this->w >= other.w);
	}

	// Array Subscriptor

	template <typename T>
	CT_MATH_FUNC_INL T & tvec4<T>::operator[](const u32 & index) {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 4, "ct::tvec4<T>: Can not access element with index %d", index);
		return (&x)[index];
	}

	template <typename T>
	CT_MATH_FUNC_INL const T & tvec4<T>::operator[](const u32 & index) const {
		__CT_MATH_ASSERT(
		    index >= 0 && index < 4, "ct::tvec4<T>: Can not access element with index %d", index);
		return (&x)[index];
	}

	// Unary operators

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator+(const tvec4<T> & vec) {
		return vec;
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator-(const tvec4<T> & vec) {
		return tvec4<T>(-vec.x, -vec.y, -vec.z, -vec.w);
	}

	// Binary operators

	// +

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator+(const tvec4<T> & other, T scalar) {
		return tvec4<T>(other.x + scalar, other.y + scalar, other.z + scalar, other.w + scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator+(T scalar, const tvec4<T> & other) {
		return tvec4<T>(scalar + other.x, scalar + other.y, scalar + other.z, scalar + other.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator+(const tvec4<T> & left, const tvec4<T> & right) {
		return tvec4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}

	// -

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator-(const tvec4<T> & other, T scalar) {
		return tvec4<T>(other.x - scalar, other.y - scalar, other.z - scalar, other.w - scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator-(T scalar, const tvec4<T> & other) {
		return tvec4<T>(scalar - other.x, scalar - other.y, scalar - other.z, scalar - other.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator-(const tvec4<T> & left, const tvec4<T> & right) {
		return tvec4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
	}

	// *

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator*(const tvec4<T> & other, T scalar) {
		return tvec4<T>(other.x * scalar, other.y * scalar, other.z * scalar, other.w * scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator*(T scalar, const tvec4<T> & other) {
		return tvec4<T>(scalar * other.x, scalar * other.y, scalar * other.z, scalar * other.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator*(const tvec4<T> & left, const tvec4<T> & right) {
		return tvec4<T>(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}

	// /

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator/(const tvec4<T> & other, T scalar) {
		return tvec4<T>(other.x / scalar, other.y / scalar, other.z / scalar, other.w / scalar);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator/(T scalar, const tvec4<T> & other) {
		return tvec4<T>(scalar / other.x, scalar / other.y, scalar / other.z, scalar / other.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL tvec4<T> operator/(const tvec4<T> & left, const tvec4<T> & right) {
		return tvec4<T>(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
	}

	// Boolean operators

	template <typename T>
	CT_MATH_FUNC_INL bool operator==(const tvec4<T> & left, const tvec4<T> & right) {
		return (left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w);
	}

	template <typename T>
	CT_MATH_FUNC_INL bool operator!=(const tvec4<T> & left, const tvec4<T> & right) {
		return (left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w);
	}

	// Vector of booleans operators only

	CT_MATH_FUNC_INL tvec4<bool> operator&&(const tvec4<bool> & left, const tvec4<bool> & right) {
		return tvec4<bool>(
		    left.x && right.x, left.y && right.y, left.z && right.z, left.w && right.w);
	}

	CT_MATH_FUNC_INL tvec4<bool> operator||(const tvec4<bool> & left, const tvec4<bool> & right) {
		return tvec4<bool>(
		    left.x || right.x, left.y || right.y, left.z || right.z, left.w || right.w);
	}

	// ostream operator
	template <typename T>
	std::ostream & operator<<(std::ostream & s, const tvec4<T> & v) {
		return s << "ct::vec4<" << type<T>::name << ">(" << v.x << ", " << v.y << ", " << v.z
		         << ", " << v.w << ')';
	}

} // namespace ct
