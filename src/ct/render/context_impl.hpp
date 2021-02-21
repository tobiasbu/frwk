
#ifndef _CHRONOTRIX_FRWK_GLCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_GLCONTEXT_HPP_

#include <memory>

#include <ct/core/utils/noncopyable.hpp>
#include <ct/render/context_config.hpp>

namespace ct {

	class Window;

	namespace internal {

		////////////////////////////////////////////////////////////
		/// @brief Represents abstract rendering context
		///
		////////////////////////////////////////////////////////////
		class ContextImpl : NonCopyable {
		public:
			virtual ~ContextImpl();

			static ContextImpl* create(Window* window, const ContextConfig & config);
		};

	}

} // namespace ct

#endif
