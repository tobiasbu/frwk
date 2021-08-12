
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_IS_ARRAY_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_IS_ARRAY_HPP_

#include <ct/core/type/traits/integral_constant.hpp>

namespace ct {

	/**
	 * @brief Check whether T is an array type.
	 *
	 * If T is array type, the value property will be equal to `true`, otherwise `false`.
	 *
	 * @tparam typename Type to check
	 */
	template <typename>
	struct is_array : public false_type {};

	/**
	 * @brief Check whether T is an array type.
	 *
	 * If T is array type, the value property will be equal to `true`, otherwise `false`.
	 *
	 * @tparam T Type to check
	 * @tparam Size Array size
	 */
	template <typename T, u32 Size>
	struct is_array<T[Size]> : public true_type {};

	/**
	 * @brief Check whether T is an array type.
	 *
	 * If T is array type, the value property will be equal to `true`, otherwise `false`.
	 *
	 * @tparam T Type to check
	 */
	template <typename T>
	struct is_array<T[]> : public true_type {};

} // namespace ct

#endif