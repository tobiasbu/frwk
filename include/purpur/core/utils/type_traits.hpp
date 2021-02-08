
#ifndef _PURPURINA_FRWK_TYPE_TRAITS_HPP_
#define _PURPURINA_FRWK_TYPE_TRAITS_HPP_

#include <purpur/core/config/compiler_features.hpp>

namespace ppr {

	///
	/// @brief Provides the non-reference type to which `T` refers.
	///
	template<class T>
	struct remove_reference {
		typedef T type; //!< type referred by T
	};

	///
	/// @brief Provides the non-reference type to which `T&` refers.
	///
	template<class T>
	struct remove_reference<T&> {
		typedef T type; //!< type referred by T
	};

	///
    /// @brief Provides the non-reference type to which `T&&` refers.
	///
	template<class T>
	struct remove_reference<T&&> {
		typedef T type; //!< type referred by T
	};

	///
	/// @brief Defines non reference type from T
	///
	///
	template <class T>
	using remove_reference_t = typename remove_reference<T>::type;

	////////////////////////////////////////////////////////////
	/// @brief Returns an _r-value_ reference to argument.
	///
	////////////////////////////////////////////////////////////
	template <class T>
	NODISCARD CONSTEXPR remove_reference_t<T>&& move(T&& t) NOEXCEPT {
		return static_cast<remove_reference_t<T>&&>(t);
	}


}

#endif
