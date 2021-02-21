
#ifndef _CHRONOTRIX_FRWK_WGLCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_WGLCONTEXT_HPP_

#include <ct/render/context_impl.hpp>

struct HGLRC__;
struct HDC__;
struct HWND__;

namespace ct {

	class Window;

	namespace internal {


		class WglContext final : public ContextImpl {
		private:
			HGLRC__ * hglrc; //!< OpenGL rendering context
			HDC__ * hdc;     //!< GDI Device context handle
			HWND__ * hwnd; 	 //!< Associate window to this context

		public:
			WglContext() = delete;
			explicit WglContext(HWND__ * hwnd, HDC__ * hdc, HGLRC__ * hglrc);

			static WglContext * create(Window* window);
		};

	} // namespace internal

} // namespace ct

#endif
