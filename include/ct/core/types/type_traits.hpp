
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_HPP_
	#define _CHRONOTRIX_FRWK_TYPE_TRAITS_HPP_

	#include <ct/config/setup.hpp>
	#include <cstddef>

namespace ct {
	////////////////////////////////////////////////////////////
	/// @defgroup type_traits Type Traits
	///
	/// @{
	///
	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////
	/// @brief Provides the non-reference type to which `T` refers.
	///
	////////////////////////////////////////////////////////////
	template <class T>
	struct remove_reference {
		using type = T; ///< type referred by T
	};

	////////////////////////////////////////////////////////////
	/// @brief Provides the non-reference type to which `T&` refers.
	///
	////////////////////////////////////////////////////////////
	template <class T>
	struct remove_reference<T &> {
		using type = T; ///< type referred by T
	};

	////////////////////////////////////////////////////////////
	/// @brief Provides the non-reference type to which `T&&` refers.
	///
	////////////////////////////////////////////////////////////
	template <class T>
	struct remove_reference<T &&> {
		using type = T; ///< type referred by T
	};

	////////////////////////////////////////////////////////////
	/// @brief Defines non reference type from T
	///
	////////////////////////////////////////////////////////////
	template <class T>
	using remove_reference_t = typename remove_reference<T>::type;

	////////////////////////////////////////////////////////////
	/// @brief Returns an _rvalue_ reference to argument.
	///
	////////////////////////////////////////////////////////////
	template <class T>
	NODISCARD CT_CONSTEXPR remove_reference_t<T> && move(T && arg) NOEXCEPT {
		return static_cast<remove_reference_t<T> &&>(arg);
	}

	template <class...>
	struct make_void { using type = void; };

	template <typename... T>
	using void_t = typename make_void<T...>::type;

	template <class T, typename = void>
	CT_CONSTEXPR bool is_type_complete = false;

	template <class T>
	CT_CONSTEXPR bool is_type_complete<T, void_t<decltype(sizeof(T))>> = true;

	template<typename T, typename TLambda>
	bool call_if_defined(TLambda&& lambda)
	{
		if CT_CONSTEXPR (is_type_complete<T>) {
			lambda(static_cast<T*>(CT_NULLPTR));
			return true;
		}
		return false;
	}

	////////////////////////////////////////////////////////////
	/// @brief Workaround to enable to make smart pointers
	/// from private or protected ctor.
	///
	/// @tparam S Instance to enable make an pointer from.
	///
	/// @see https://stackoverflow.com/a/8147326
	////////////////////////////////////////////////////////////
	template <typename S>
	struct enable_make : public S {
		////////////////////////////////////////////////////////////
		/// @brief Constructs a instance S by forwarding ctor arguments
		///
		/// @tparam T ctor arguments
		/// @param t Arguments
		////////////////////////////////////////////////////////////
		template <typename... T>
		enable_make(T &&... t) : S(FWD(t)...) {}
	};
	
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

	template <typename T>
	inline void swap(T & x, T & y) NOEXCEPT {
		T tmp = MOV(x);
		x = MOV(y);
		y = MOV(tmp);
	}

	/// @}

} // namespace ct

#endif

////////////////////////////////////////////////////////////
/// @file type_traits.hpp
/// Detailed description goes here
/// @ingroup core
///
////////////////////////////////////////////////////////////
