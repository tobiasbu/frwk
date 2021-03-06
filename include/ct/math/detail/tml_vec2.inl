
namespace ct {

	namespace detail {

		// Default

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T>::vec2() : x(0),
		                                           y(0) {}

		// Explicit constructors

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T>::vec2(T _x, T _y) : x(_x),
		                                                     y(_y) {}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T>::vec2(T scalar) : x(scalar),
		                                                   y(scalar) {}

		// Conversion constructors

		template <typename T>
		template <typename X, typename Y>
		CT_FORCEINLINE CONSTEXPR vec2<T>::vec2(X _x, Y _y)
		: x(static_cast<T>(_x)),
		  y(static_cast<T>(_y)) {}

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T>::vec2(const vec2<U> & v2)
		: x(static_cast<T>(v2.x)),
		  y(static_cast<T>(v2.y)) {}

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T>::vec2(const vec3<U> & v3)
		: x(static_cast<T>(v3.x)),
		  y(static_cast<T>(v3.y)) {}

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T>::vec2(const vec4<U> & v4)
		: x(static_cast<T>(v4.x)),
		  y(static_cast<T>(v4.y)) {}

		// Assign operators

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator=(const vec2<U> & other) {
			this->x = static_cast<T>(other.x);
			this->y = static_cast<T>(other.y);
			return *this;
		};

		// Unary operators

		// +=

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator+=(U scalar) {
			this->x += static_cast<T>(scalar);
			this->y += static_cast<T>(scalar);
			return *this;
		}

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator+=(const vec2<U> & other) {
			this->x += static_cast<T>(other.x);
			this->y += static_cast<T>(other.y);
			return *this;
		}

		// -=

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator-=(U scalar) {
			this->x -= static_cast<T>(scalar);
			this->y -= static_cast<T>(scalar);
			return *this;
		}

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator-=(const vec2<U> & other) {
			this->x -= static_cast<T>(other.x);
			this->y -= static_cast<T>(other.y);
			return *this;
		}

		// *=

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator*=(U scalar) {
			this->x *= static_cast<T>(scalar);
			this->y *= static_cast<T>(scalar);
			return *this;
		}

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator*=(const vec2<U> & other) {
			this->x *= static_cast<T>(other.x);
			this->y *= static_cast<T>(other.y);
			return *this;
		}

		// /=
		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator/=(U scalar) {
			this->x /= static_cast<T>(scalar);
			this->y /= static_cast<T>(scalar);
			return *this;
		}

		template <typename T>
		template <typename U>
		CT_FORCEINLINE CONSTEXPR vec2<T> & vec2<T>::operator/=(const vec2<U> & other) {
			this->x /= static_cast<T>(other.x);
			this->y /= static_cast<T>(other.y);
			return *this;
		}

		// Array Subscriptor

		template <typename T>
		CT_FORCEINLINE CONSTEXPR T & vec2<T>::operator[](const u32 & index) {
			__CT_MATH_ASSERT(index >= 0 && index < 2, "ct::vec2<T> Can not access element %d", index);
			return index ? y : x;
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR const T & vec2<T>::operator[](const u32 & index) const {
			__CT_MATH_ASSERT(index >= 0 && index < 2, "ct::vec2<T> Can not access element %d", index);
			return index ? y : x; // return (&x)[index];
		}

		// Unary operators

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator+(const vec2<T> & vec) {
			return vec;
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator-(const vec2<T> & vec) {
			return vec2<T>(-vec.x, -vec.y);
		}

		// Binary operators

		// +

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator+(const vec2<T> & other, T scalar) {
			return vec2<T>(other.x + scalar, other.y + scalar);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator+(T scalar, const vec2<T> & other) {
			return vec2<T>(scalar + other.x, scalar + other.y);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator+(const vec2<T> & left, const vec2<T> & right) {
			return vec2<T>(left.x + right.x, left.y + right.y);
		}

		// -

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator-(const vec2<T> & other, T scalar) {
			return vec2<T>(other.x - scalar, other.y - scalar);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator-(T scalar, const vec2<T> & other) {
			return vec2<T>(scalar - other.x, scalar - other.y);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator-(const vec2<T> & left, const vec2<T> & right) {
			return vec2<T>(left.x - right.x, left.y - right.y);
		}

		// *

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator*(const vec2<T> & other, T scalar) {
			return vec2<T>(other.x * scalar, other.y * scalar);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator*(T scalar, const vec2<T> & other) {
			return vec2<T>(scalar * other.x, scalar * other.y);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator*(const vec2<T> & left, const vec2<T> & right) {
			return vec2<T>(left.x * right.x, left.y * right.y);
		}

		// /

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator/(const vec2<T> & other, T scalar) {
			return vec2<T>(other.x / scalar, other.y / scalar);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator/(T scalar, const vec2<T> & other) {
			return vec2<T>(scalar / other.x, scalar / other.y);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR vec2<T> operator/(const vec2<T> & left, const vec2<T> & right) {
			return vec2<T>(left.x / right.x, left.y / right.y);
		}

		// Boolean operators

		template <typename T>
		CT_FORCEINLINE CONSTEXPR bool operator==(const vec2<T> & left, const vec2<T> & right) {
			return (left.x == right.x) && (left.y == right.y);
		}

		template <typename T>
		CT_FORCEINLINE CONSTEXPR bool operator!=(const vec2<T> & left, const vec2<T> & right) {
			return (left.x != right.x || left.y != right.y);
		}

		// Vector of booleans operators only

		CT_FORCEINLINE CONSTEXPR vec2<bool> operator&&(const vec2<bool> & left, const vec2<bool> & right) {
			return vec2<bool>(left.x && right.x, left.y && right.y);
		}

		CT_FORCEINLINE CONSTEXPR vec2<bool> operator||(const vec2<bool> & left, const vec2<bool> & right) {
			return vec2<bool>(left.x || right.x, left.y || right.y);
		}
	}
}
