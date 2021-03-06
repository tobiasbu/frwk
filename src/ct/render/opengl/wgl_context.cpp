
#include <iostream>
#include <windows.h>

#include <ct/config/types.hpp>
#include <ct/platform/window.hpp>
#include <ct/render/opengl/wgl_context.hpp>
#include <ct/render/win32/win32_internal.hpp>

namespace ct {

	namespace internal {

		namespace detail {
			HMODULE opengl32_module = NULL;

			PIXELFORMATDESCRIPTOR create_pixel_format(const ContextConfig & config) {
				DWORD dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
				BYTE iPixelType = PFD_TYPE_RGBA;
				BYTE cColorBits = config.color_bits;
				BYTE alphaBuffer = 0;

				if (cColorBits >= 32) {
					cColorBits = 32;
					alphaBuffer = 8;
				}
				// clang-format off
				PIXELFORMATDESCRIPTOR pfd = {
					sizeof(PIXELFORMATDESCRIPTOR), // Size of PixelFormat struct
					1,                             // Version Number
					dwFlags,    // Flags that specify properties of the pixel buffer
					iPixelType, // Specifies the type of pixel data
					cColorBits, // bits per pixel - Specifies the number of color bitplanes in eachcolor buffer
					0, 0, 0, 0,
					0,           // Color Bits Ignored
					alphaBuffer, // Alpha buffer
					0,           // Shift Bit Ignored
					0,           // No Accumulation Buffer
					0, 0, 0,
					0,              // Accumulation Bits Ignored
					0,              // Z-Buffer (Depth Buffer)
					0,              // No Stencil Buffer
					0,              // No Auxiliary Buffer
					PFD_MAIN_PLANE, // Main Drawing Layer
					0,              // Reserved
					0, 0,
					0 // Layer Masks Ignored
				};
				// clang-format on
				return pfd;
			}

			bool init_WGL() {
				if (opengl32_module) {
					return true;
				}

				opengl32_module = LoadLibraryA("opengl32.dll");
				if (!opengl32_module) {
					return false;
				}

				// Create dummy context to retrieve ARB extensions
				PIXELFORMATDESCRIPTOR pfd = create_pixel_format(ContextConfig());
				auto hdc = GetDC(internal::get_helper_window());

				i32 pixelFormat = ChoosePixelFormat(hdc, &pfd);
				if (!SetPixelFormat(hdc, pixelFormat, &pfd)) {
					return false;
				}

				auto hglrc = wglCreateContext(hdc);
				if (!hglrc) {
					return false;
				}

				auto current_hdc = wglGetCurrentDC();
				auto current_hglrc = wglGetCurrentContext();

				if (!wglMakeCurrent(hdc, hglrc)) {
					wglMakeCurrent(current_hdc, current_hglrc);
					wglDeleteContext(hglrc);
					return false;
				}

				wglMakeCurrent(current_hdc, current_hglrc);
				wglDeleteContext(hglrc);
				return true;
			}
		} // namespace detail

		WglContext::WglContext(HWND hwnd, HDC hdc, HGLRC hglrc)
		: hwnd(hwnd),
		  hdc(hdc),
		  hglrc(hglrc) {}

		void WglContext::make_current() {
			if (hwnd != NULL) {
				if (wglMakeCurrent(hdc, hglrc)) {
				} else {
				}
			} else {
				if (!wglMakeCurrent(NULL, NULL)) {
				}
			}
		}
		void WglContext::swap_buffers() {
			SwapBuffers(hdc);
		}

		get_proc_address_fn WglContext::get_proc_address(cstr procname) {
			const auto proc = (get_proc_address_fn)wglGetProcAddress(procname);
			if (proc) {
				return proc;
			}

			return (get_proc_address_fn)GetProcAddress(detail::opengl32_module, procname);
		}

		WglContext * WglContext::create(Window * window, const ContextConfig & config) {
			if (!detail::init_WGL()) {
				std::cout << "Failed to initialize Wgl" << std::endl;
				return nullptr;
			}

			auto hWnd = window->get_handle();

			// window handle to device context
			HDC hDc = GetDC(hWnd);

			PIXELFORMATDESCRIPTOR pfd = detail::create_pixel_format(config);
			i32 pixelFormat = ChoosePixelFormat(hDc, &pfd);
			if (!pixelFormat) {
				std::cout << "Fail to create pixel format" << std::endl;
			}

			if (!DescribePixelFormat(hDc, pixelFormat, sizeof(pfd), &pfd)) {
				std::cout << "Failed to describe PFD for selected pixel format" << std::endl;
				return nullptr;
			}

			if (!SetPixelFormat(hDc, pixelFormat, &pfd)) {
				std::cout << "Fail to set pixel format" << std::endl;
			}

			// openGL rendering context
			HGLRC hglrc = wglCreateContext(hDc);

			if (!hglrc) {
				std::cout << "Fail to create OpenGL rendering context" << std::endl;
			}

			if (wglMakeCurrent(hDc, hglrc) == false) {
				std::cout << "wglMakeCurrent failed" << std::endl;
			}

			return new WglContext(hWnd, hDc, hglrc);
		}

	} // namespace internal

} // namespace ct
