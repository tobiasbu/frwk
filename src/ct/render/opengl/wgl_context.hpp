
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

			void make_current() override;
			void swap_buffers() override;

			static getProcAddressCb get_proc_address(cstr procname);

			static WglContext * create(Window* window, const ContextConfig & config);
		};

	} // namespace internal

} // namespace ct

#endif
