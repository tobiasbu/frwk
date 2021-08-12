
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_

#include <ct/config.hpp>

namespace ct {

	/**
	 * @brief Base class for C++ type traits.
	 * Wraps a static constant of specified type.
	 *
	 * @tparam T Type
	 * @tparam Value Value
	 */
	template <typename T, T Value>
	struct integral_constant {
		using value_type = T;
		using type = integral_constant<T, Value>;
		static CT_CONSTEXPR T value = Value;

		/**
		 * @brief Returns wrapped value
		 *
		 * @return value_type
		 */
		CT_CONSTEXPR operator value_type() const NOEXCEPT {
			return value;
		}

		/**
		 * @brief Returns wrapped value.
		 * Source of compile-time function object.
		 *
		 * @return value_type
		 */
		CT_CONSTEXPR value_type operator()() const NOEXCEPT {
			return value;
		}
	};

	template <typename T, T Value>
	CT_CONSTEXPR T integral_constant<T, Value>::value;

	/**
	 * @brief Instance of integral_constant to represent `boolean` type with `true` value.
	 */
	using true_type = integral_constant<bool, true>;

	/**
	 * @brief Instance of integral_constant to represent `boolean` type with `false` value.
	 */
	using false_type = integral_constant<bool, false>;

} // namespace ct

#endif