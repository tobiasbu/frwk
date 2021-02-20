
#ifndef _CHRONOTRIX_FRWK_GLCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_GLCONTEXT_HPP_

#include <memory>

namespace ct {

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

} // namespace ct

#endif
