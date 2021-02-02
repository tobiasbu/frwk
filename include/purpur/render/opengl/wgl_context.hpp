
#ifndef _PURPURINA_FRWK_WGLCONTEXT_HPP_
#define _PURPURINA_FRWK_WGLCONTEXT_HPP_

#include <purpur/render/opengl/gl_context.hpp>
#include <windows.h>

namespace ppr {

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

} // namespace ppr

#endif
