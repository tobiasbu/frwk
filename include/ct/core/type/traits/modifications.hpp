
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_MODIFICATIONS_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_MODIFICATIONS_HPP_

#include <ct/core/type/traits/remove_reference.hpp>

namespace ct {

	template <class T>
	struct type_identity {
		using type = T;
	};

	/**
	 * @brief Remove the topmost `const` qualifer
	 *
	 * @tparam T Type to remove const
	 */
	template <class T>
	struct remove_const {
		using type = T;
	};

	/**
	 * @brief Remove the topmost `const` qualifer
	 *
	 * @tparam T Type to remove const
	 */
	template <class T>
	struct remove_const<T const> {
		using type = T;
	};

	template <class T>
	using remove_const_t = typename remove_const<T>::type;

	/**
	 * @brief Remove the topmost `volatile` qualifer
	 *
	 * @tparam T Type to remove volatile
	 */
	template <class T>
	struct remove_volatile {
		using type = T;
	};

	/**
	 * @brief Remove the topmost `volatile` qualifer
	 *
	 * @tparam T Type to remove volatile
	 */
	template <class T>
	struct remove_volatile<T volatile> {
		using type = T;
	};

	template <class T>
	using remove_volatile_t = typename remove_volatile<T>::type;

	/**
	 * @brief Removes the topmost `const`, or the topmost `volatile`, or both, if present.
	 *
	 * @tparam T Type to remove volatile, const or both
	 */
	template <class T>
	struct remove_cv {
		using type = typename remove_const<typename remove_volatile<T>::type>::type;
	};

	template <class T>
	using remove_cv_t = typename remove_cv<T>::type;

	/**
	 * @brief Removes array declaration and provides it's type.
	 *
	 * If T is an array of some type X, provides the member type
	 * equal to X, otherwise type is T.
	 *
	 * NOTE: If T is a multidimensional array, only the first dimension is removed.
	 *
	 * @tparam T
	 */
	template <class T>
	struct remove_extent {
		using type = T;
	};

	template <class T>
	struct remove_extent<T[]> {
		using type = T;
	};

	template <class T, u32 N>
	struct remove_extent<T[N]> {
		using type = T;
	};

	template <class T>
	using remove_extent_t = typename remove_extent<T>::type;

	namespace detail {
		template <class T>
		CT_CONSTEXPR auto __try_add_pointer(i32)
		    -> type_identity<typename remove_reference<T>::type *>;

		template <class T>
		CT_CONSTEXPR auto __try_add_pointer(...) -> type_identity<T>;
	} // namespace detail

	/**
	 * @brief Add pointer to T.
	 *
	 * If T is a reference type, then provides type which is a pointer to the referred type.
	 *
	 * Otherwise, if T names an object type, a function type that is not cv- or ref-qualified,
	 * or a (possibly cv-qualified) void type, provides the member typedef type which is the type T*.
	 *
	 * Otherwise (if T is a cv- or ref-qualified function type),
	 * provides the member typedef type which is the type T.
	 *
	 * @tparam T
	 */
	template <class T>
	struct add_pointer : public decltype(detail::__try_add_pointer<T>(0)) {};

	template <class T>
	using add_pointer_t = typename add_pointer<T>::type;

} // namespace ct

#endif