
#include <purpur/platform/win32/win32_detail.hpp>
#include <purpur/platform/win32/win32_window.hpp>
#include <purpur/platform/window_style.hpp>

namespace ppr {

	namespace internal {

		////////////////////////////////////////////////////////////
		/// Internal Apis
		////////////////////////////////////////////////////////////
		const wchar_t * toWchar(cstr buffer) {
			int buffer_size = MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, 0);
			LPWSTR wbuffer = (LPWSTR)malloc(buffer_size);
			MultiByteToWideChar(CP_ACP, 0, buffer, -1, &wbuffer[0], buffer_size);
			return wbuffer;
		}

		DWORD parseStyle(const uint32 & style) {
			DWORD dwStyle = 0;

			if (style == WindowStyle::Borderless) {
				dwStyle = WS_POPUP;
			} else {
				bool shouldBeClosable = false;

				if (style & WindowStyle::Title) {
					dwStyle |= WS_CAPTION;
				}

				if (style & WindowStyle::Resize) {
					dwStyle |= WS_THICKFRAME | WS_MAXIMIZEBOX;
					shouldBeClosable = true;
				}

				if (style & WindowStyle::Minimize) {
					dwStyle |= WS_MINIMIZEBOX;
					shouldBeClosable = true;
				}

				if (style & WindowStyle::Close || shouldBeClosable) {
					dwStyle |= WS_SYSMENU;
				}
			}
			return dwStyle;
		}

		Win32Window::Win32Window(uint32 width, uint32 height, cstr title, uint32 style)
		: handle(nullptr) {
			bool isFullscreen = false;

			// Retrieves a handle to a device context (DC) for the client area of a specified window
			// or for the entire screen
			HDC screenDC = GetDC(NULL);
			// Compute window position and size
			int32 left = (GetDeviceCaps(screenDC, HORZRES) - static_cast<int>(width)) / 2;
			int32 top = (GetDeviceCaps(screenDC, VERTRES) - static_cast<int>(height)) / 2;
			ReleaseDC(NULL, screenDC);

			// if (!isFullscreen) {
			// 	RECT rect = RECT {0, 0, width, height};
			// 	AdjustWindowRect(&rect, win32Style, false);
			// 	width = rect.right - rect.left;
			// 	height = rect.bottom - rect.top;
			// }

			const wchar_t * titleWchar = toWchar(title);
			if (!titleWchar) {
				// std::cerr << "Invalid title" << std::endl;
				return;
			}

			// clang-format off
			handle = CreateWindowExW(WS_EX_APPWINDOW,
				__PPR_WNDCLASSNAME,
				titleWchar,
				parseStyle(style),
				left,
				top,
				width,
				height,
				NULL,
				NULL,
				GetModuleHandle(NULL),
				NULL);
			// clang-format on

			if (!handle) {
				// std::cerr << "Could no create window" << std::endl;
				return;
				/* ShowWindow(handle, 1);
				UpdateWindow(handle);*/
			}

			// if (style == 0) {
			// 	SetWindowLong(handle, GWL_STYLE, 0 );
			// }

			SetPropW(handle, L"PPR", this);
		}

		Win32Window::~Win32Window() {
			dispose();
		}

		void Win32Window::setVisible(bool visible) {
			ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
		}

		WindowHandle Win32Window::getHandle() const {
			return handle;
		}

		bool Win32Window::isVisible() const {
			return IsWindowVisible(handle);
		}

		void Win32Window::pool() {
			MSG message;
			while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&message);
				DispatchMessageW(&message);
			}
		}

		void Win32Window::onEvent(UINT message, WPARAM wParam, LPARAM lParam) {
			if (!handle) {
				return;
			}
			// Event event;
			// event.type = message;
		}

		void Win32Window::dispose() {
			if (handle) {
				RemovePropW(handle, L"PPR");
				DestroyWindow(handle);
				handle = nullptr;
			}
		}

		// LRESULT CALLBACK Win32Window::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM
		// lParam)
	} // namespace internal
} // namespace ppr
