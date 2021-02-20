
#ifndef _CHRONOTRIX_FRWK_WGLCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_WGLCONTEXT_HPP_

#include <ct/render/opengl/gl_context.hpp>
#include <windows.h>

namespace ct {

	namespace internal {

		/**
		 * \brief Represents abstract OpenGL context
		 */
		class WglContext : public GlContext {
		private:
			HGLRC hglrc; //!< OpenGL rendering context
			HDC hdc;     //!< GDI Device context handle
			HWND window; //!< Associate window to this context

		public:
			WglContext();

			WglContext * create() const;
		};

	} // namespace internal

} // namespace ct

#endif
