
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_IS_FUNCTION_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_IS_FUNCTION_HPP_

#include <ct/core/type/traits/integral_constant.hpp>

#if defined(CT_CXX_HAS_NOEXCEPT)
	#define __CT_TPARAM_IS_NOEXCEPT , bool IsNoExcept
	#define __CT_QUALIF_IS_NOEXCEPT NOEXCEPT (IsNoExcept)
#else
	#define __CT_TPARAM_IS_NOEXCEPT
	#define __CT_QUALIF_IS_NOEXCEPT
#endif

namespace ct {

	/**
	 * @brief Check whether T is a function type.
	 * If T is function type, the value property will be equal to `true`, otherwise `false`.
	 *
	 * NOTE: Types like std::function, lambdas, typenames with overloaded operator() and
	 * pointers to functions don't count as function types.
	 */
	template <typename>
	struct is_function : public false_type {};

	/// Regular function

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) __CT_QUALIF_IS_NOEXCEPT> : public true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) & __CT_QUALIF_IS_NOEXCEPT> : public true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) && __CT_QUALIF_IS_NOEXCEPT> : public true_type {};

	/// Specialization for variadic functions such as printf(...)

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) __CT_QUALIF_IS_NOEXCEPT> : public true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) & __CT_QUALIF_IS_NOEXCEPT> : public true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) && __CT_QUALIF_IS_NOEXCEPT> : public true_type {};

	/// Specialization for function that have const

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) const __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) const & __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) const && __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	/// Specialization for variadic functions that have const

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) const __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) const & __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) const && __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	/// Specialization for functions that have volatile qualifier

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) volatile __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) volatile & __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) volatile && __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	/// Specialization for variadic functions with volatile qualifier

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) volatile __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) volatile & __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) volatile && __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	/// Specialization for functions that have cv-qualifier

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) const volatile __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) const volatile & __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args...) const volatile && __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	/// Specialization for variadic functions that have cv-qualifier

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) const volatile __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) const volatile & __CT_QUALIF_IS_NOEXCEPT> : true_type {};

	template <typename Ret, typename... Args __CT_TPARAM_IS_NOEXCEPT>
	struct is_function<Ret(Args......) const volatile && __CT_QUALIF_IS_NOEXCEPT> : true_type {};
} // namespace ct

#undef __CT_TPARAM_IS_NOEXCEPT
#undef __CT_QUALIF_IS_NOEXCEPT

#endif