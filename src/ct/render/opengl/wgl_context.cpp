
#include <windows.h>
#include <iostream>

#include <ct/core/types.hpp>
#include <ct/platform/window.hpp>

#include <ct/render/opengl/win32_internal.hpp>
#include <ct/render/opengl/wgl_context.hpp>

namespace ct {

	namespace internal {

		namespace detail {
			HMODULE opengl32;

			PIXELFORMATDESCRIPTOR create_pixel_format() {
				DWORD dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
				BYTE iPixelType = PFD_TYPE_RGBA;
				BYTE cColorBits = 24;
				BYTE alphaBuffer = cColorBits == 32 ? 8 : 0;

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

				return pfd;
			}

			bool init_WGL() {
				if (opengl32) {
					return true;
				}

				opengl32 = LoadLibraryA("opengl32.dll");
				if (!opengl32) {
					return false;
				}

				// Create dummy context to retrieve ARB extensions
				PIXELFORMATDESCRIPTOR pfd = create_pixel_format();
				auto hdc = GetDC(internal::get_helper_window());

				int32 pixelFormat = ChoosePixelFormat(hdc, &pfd);
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
		}

		WglContext::WglContext(HWND hwnd, HDC hdc, HGLRC hglrc)
		:
		hwnd(hwnd),
		hdc(hdc),
		hglrc(hglrc)
		{
		}

		WglContext * WglContext::create(Window* window) {

			if (!detail::init_WGL()) {
				std::cout << "Failed to initialize Wgl" << std::endl;
				return nullptr;
			}

			auto hWnd = window->get_handle();

			// window handle to device context
			HDC hDc = GetDC(hWnd);

			PIXELFORMATDESCRIPTOR pfd = detail::create_pixel_format();
			int32 pixelFormat = ChoosePixelFormat(hDc, &pfd);

			if (pixelFormat) {
				if (!SetPixelFormat(hDc, pixelFormat, &pfd)) {
					std::cout << "Fail to create pixel format" << std::endl;
				}
			} else {
				// error
					std::cout << "Fail to choose pixel format" << std::endl;
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
