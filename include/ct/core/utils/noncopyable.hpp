
#ifndef _CHRONOTRIX_FRWK_NONCOPYABLE_HPP_
#define _CHRONOTRIX_FRWK_NONCOPYABLE_HPP_

#include <ct/core/config/compiler_features.hpp>


namespace ct {

	///
	/// @brief Non copyable object
	///
	class NonCopyable {
	protected:
#if defined(CT_CXX11_DEFAULT_FUNCTIONS)
		constexpr NonCopyable() = default;
		~NonCopyable() = default;
#else
		NonCopyable() {}
		~NonCopyable() {}
#endif

#if defined(CT_CXX11_DELETE_FUNCTIONS)
		///
		/// @brief Non copyable
		///
		NonCopyable(const NonCopyable &) = delete;
		///
		/// @brief Copy assignment is not permited
		///
		NonCopyable & operator=(const NonCopyable &) = delete;
#else
	private:
		NonCopyable(const NonCopyable &);
		NonCopyable & operator=(const NonCopyable &);
#endif
	};
} // namespace ct

#endif
