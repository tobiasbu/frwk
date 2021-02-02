
#ifndef _PURPURINA_FRWK_GLCONTEXT_HPP_
#define _PURPURINA_FRWK_GLCONTEXT_HPP_

#include <memory>

namespace ppr {

	/**
	 * \brief Represents abstract OpenGL context
	 */
	class GlContext {
	public:
		/**
		 * \brief Create OpenGL context
		 */
		static std::unique_ptr<GlContext> create();
	};

}// namespace ppr

#endif
