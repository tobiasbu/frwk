
#ifndef _CHRONOTRIX_FRWK_GLCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_GLCONTEXT_HPP_

#include <ct/core/utils/noncopyable.hpp>
#include <ct/platform/context_config.hpp>

namespace ct {

	class Window;

	namespace internal {

		////////////////////////////////////////////////////////////
		/// @brief Represents abstract rendering context
		///
		////////////////////////////////////////////////////////////
		class ContextImpl : NonCopyable {
		public:
			virtual ~ContextImpl() {}

			virtual void make_current() = 0;
			virtual void swap_buffers() = 0;
		};

	} // namespace internal

} // namespace ct

#endif
