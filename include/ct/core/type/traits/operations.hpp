
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_OPERATIONS_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_OPERATIONS_HPP_

#include <ct/config/setup.hpp>
#include <ct/core/type/traits/remove_reference.hpp>

namespace ct {

	////////////////////////////////////////////////////////////
	/// @brief Returns an _rvalue_ reference to argument.
	///
	////////////////////////////////////////////////////////////
	template <class T>
	NODISCARD CT_CONSTEXPR remove_reference_t<T> && move(T && arg) NOEXCEPT {
		return static_cast<remove_reference_t<T> &&>(arg);
	}

	template <typename T>
	inline void swap(T & x, T & y) NOEXCEPT {
		T tmp = MOV(x);
		x = MOV(y);
		y = MOV(tmp);
	}

	////////////////////////////////////////////////////////////
	/// @brief `static_cast` to `rvalue` reference.
	///
	/// This macro is an version of move semantics.
	/// The reason to use this macro is that improves compilation time.
	///
	/// @see https://www.foonathan.net/2020/09/move-forward/#self-documenting-code
	///
	////////////////////////////////////////////////////////////
	#define MOV(...) static_cast<ct::remove_reference_t<decltype(__VA_ARGS__)> &&>(__VA_ARGS__)

	////////////////////////////////////////////////////////////
	/// @def FWD(...args)
	/// @brief Forward an _lvalue_ as either an _lvalue_
	/// or an rvalue
	///
	////////////////////////////////////////////////////////////
	#define FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

} // namespace ct

#endif