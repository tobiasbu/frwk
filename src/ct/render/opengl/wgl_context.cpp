
#include <ct/core/types.hpp>
#include <ct/render/opengl/wgl_context.hpp>

namespace ct {

	namespace internal {

		namespace {
			void createDummyContext() {}

			PIXELFORMATDESCRIPTOR createPixelFormat() {
				DWORD dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
				BYTE iPixelType = PFD_TYPE_RGBA;
				BYTE cColorBits = 32;
				BYTE alphaBuffer = cColorBits == 32 ? 8 : 0;

				PIXELFORMATDESCRIPTOR pfd = {
				    sizeof(PIXELFORMATDESCRIPTOR), // Size of PixelFormat struct
				    1,                             // Version Number
				    dwFlags,    // Flags that specify properties of the pixel buffer
				    iPixelType, // Specifies the type of pixel data
				    cColorBits, // bits per pixel - Specifies the number of color bitplanes in each
				                // color buffer
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
		} // namespace

		WglContext::WglContext() {
			// window handle to device context
			// HDC hDc = GetDC(hWnd);

			// PIXELFORMATDESCRIPTOR pfd = createPixelFormat();
			// int32 pixelFormat = ChoosePixelFormat(hDc, &pfd);

			// if (pixelFormat) {
			//	if (!SetPixelFormat(hDc, pixelFormat, &pfd)) {

			//	}
			//} else {
			//	// error
			//}

			// HGLRC ourOpenGLRenderingContext = wglCreateContext(hDc);
		}

	} // namespace internal

} // namespace ct
