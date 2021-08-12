
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_HPP_

#include <ct/core/type/traits/integral_constant.hpp>
#include <ct/core/type/traits/operations.hpp>
#include <ct/core/type/traits/modifications.hpp>
#include <ct/core/type/traits/transformations.hpp>


namespace ct {


    ////////////////////////////////////////////////////////////
	/// @defgroup type_traits Type Traits
	///
	/// @{
	///
	////////////////////////////////////////////////////////////



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



	/// @}

} // namespace ct

#endif

////////////////////////////////////////////////////////////
/// @file type_traits.hpp
/// Detailed description goes here
/// @ingroup core
///
////////////////////////////////////////////////////////////
