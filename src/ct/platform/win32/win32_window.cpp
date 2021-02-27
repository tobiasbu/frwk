
#include <ct/platform/window_style.hpp>
#include <ct/platform/detail/win32_detail.hpp>

#include <ct/platform/win32/win32_window.hpp>

namespace ct {

	namespace internal {

		/**
		 * Convert const char * to wchar_t
		 */
		WCHAR* to_wchar(cstr input) {
			int buffer_count = MultiByteToWideChar(CP_ACP, 0, input, -1, NULL, 0);

			if (!buffer_count) {
				return NULLPTR;
			}

			WCHAR* output = (WCHAR*)calloc(buffer_count, sizeof(WCHAR));

			if (!MultiByteToWideChar(CP_UTF8, 0, input, -1, &output[0], buffer_count)) {
				free(output);
				return NULLPTR;
			}

			return output;
		}

		DWORD parse_style(const u32 & style) {
			DWORD dwStyle = 0;

			if (style == WindowStyle::Borderless) {
				dwStyle = WS_POPUP;
			} else {
				bool shouldBeClosable = false;

				if (style & WindowStyle::Title) {
					dwStyle |= WS_CAPTION;
				}

				if (style & WindowStyle::Resize) {
					dwStyle |= WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
					shouldBeClosable = true;
				}

				if (style & WindowStyle::Close || shouldBeClosable) {
					dwStyle |= WS_SYSMENU;
				}
			}
			return dwStyle;
		}

		Win32Window::Win32Window(HWND handle)
		: handle(handle) {

		}

		Win32Window::~Win32Window() {
			dispose();
		}

		Win32Window* Win32Window::create(const WindowProperties & props) {
			bool isFullscreen = false;

			// Retrieves a handle to a device context (DC) for the client area of a specified window
			// or for the entire screen
			HDC screenDC = GetDC(NULL);
			// Compute window position and size
			i32 left = (GetDeviceCaps(screenDC, HORZRES) - static_cast<int>(props.width)) / 2;
			i32 top = (GetDeviceCaps(screenDC, VERTRES) - static_cast<int>(props.height)) / 2;
			ReleaseDC(NULL, screenDC);

			// if (!isFullscreen) {
			// 	RECT rect = RECT {0, 0, width, height};
			// 	AdjustWindowRect(&rect, win32Style, false);
			// 	width = rect.right - rect.left;
			// 	height = rect.bottom - rect.top;
			// }

			WCHAR * titleWchar = to_wchar(props.title);
			if (!titleWchar) {
				// std::cerr << "Invalid title" << std::endl;
				return NULLPTR;
			}

			// clang-format off
			HWND handle = CreateWindowExW(WS_EX_APPWINDOW,
				__CT_WNDCLASSNAME,
				titleWchar,
				parse_style(props.style),
				left,
				top,
				props.width,
				props.height,
				NULL,
				NULL,
				GetModuleHandle(NULL),
				NULL);
			// clang-format on

			free(titleWchar);

			if (!handle) {
				// std::cerr << "Could no create window" << std::endl;
				return NULLPTR;
			}


			auto win = new Win32Window(handle);
			SetPropW(handle, L"CT", win);
			return win;
		}

		void Win32Window::set_visible(bool visible) {
			ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
		}

		WindowHandle Win32Window::get_handle() const {
			return handle;
		}

		bool Win32Window::is_visible() const {
			return IsWindowVisible(handle);
		}

		void Win32Window::on_event(UINT message, WPARAM wParam, LPARAM lParam) {
			if (!handle) {
				return;
			}
			// Event event;
			// event.type = message;
		}

		void Win32Window::dispose() {
			if (handle) {
				RemovePropW(handle, L"CT");
				DestroyWindow(handle);
				handle = nullptr;
			}
		}
	} // namespace internal
} // namespace ct
