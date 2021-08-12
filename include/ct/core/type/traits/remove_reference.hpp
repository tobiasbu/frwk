
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_REMOVE_REFERENCE_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_REMOVE_REFERENCE_HPP_

#include <ct/config/setup.hpp>

namespace ct {

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

} // namespace ct

#endif