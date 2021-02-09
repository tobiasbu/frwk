
#ifndef _PURPURINA_FRWK_NONCOPYABLE_HPP_
#define _PURPURINA_FRWK_NONCOPYABLE_HPP_

#include <purpur/core/config/compiler_features.hpp>

namespace ppr {

	///
	/// @brief Non copyable instance
	///
	class NonCopyable {
	protected:
#if defined(PPR_CXX11_DEFAULT_FUNCTIONS)
		constexpr NonCopyable() = default;
		~NonCopyable() = default;
#else
		NonCopyable() {}
		~NonCopyable() {}
#endif

#if defined(PPR_CXX11_DELETE_FUNCTIONS)
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
} // namespace ppr

#endif
