
#include <ct/platform/detail/win32_detail.hpp>
#include <ct/platform/win32/win32_window.hpp>
#include <ct/platform/window_style.hpp>
#include <iostream>

namespace ct {

	namespace internal {

		/**
		 * Convert const char * to wchar_t
		 */
		WCHAR * to_wchar(cstr input) {
			int buffer_count = MultiByteToWideChar(CP_ACP, 0, input, -1, NULL, 0);

			if (!buffer_count) {
				return NULLPTR;
			}

			WCHAR * output = (WCHAR *)calloc(buffer_count, sizeof(WCHAR));

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

		Win32Window::Win32Window(HWND handle) : handle(handle) {}

		Win32Window::~Win32Window() {
			dispose();
		}

		Win32Window * Win32Window::create(const WindowProperties & props) {
			bool isFullscreen = false;

			WCHAR * titleWchar = to_wchar(props.title);
			if (!titleWchar) {
				// std::cerr << "Invalid title" << std::endl;
				return NULLPTR;
			}

			u32 window_style = parse_style(props.style);
			i32 width;
			i32 height;

			if (!isFullscreen) {
				RECT rect = {0, 0, static_cast<i32>(props.width), static_cast<i32>(props.height)};
				AdjustWindowRect(&rect, window_style, false);
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;
			}

			// Retrieves a handle to a device context (DC) for the client area of a specified window
			// or for the entire screen
			HDC screenDC = GetDC(NULL);
			// Compute window position and size
			i32 left = (GetDeviceCaps(screenDC, HORZRES) - width) / 2;
			i32 top = (GetDeviceCaps(screenDC, VERTRES) - height) / 2;
			ReleaseDC(NULL, screenDC);

			// clang-format off
			HWND handle = CreateWindowExW(WS_EX_APPWINDOW,
				__CT_WNDCLASSNAME,
				titleWchar,
				window_style,
				left,
				top,
				width,
				height,
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


		WindowHandle Win32Window::get_handle() const {
			return handle;
		}

		vec2u Win32Window::get_content_size() const {
			RECT rect;
			vec2u size;
			if (GetClientRect(handle, &rect)) {
				size.x = rect.right - rect.left;
				size.y = rect.bottom - rect.top;
			}
			return size;
		}

		recti Win32Window::get_frame() const {
			RECT rect = {NULL};
			recti frame;
			if (GetWindowRect(handle, &rect)) {
				frame.x = rect.left;
				frame.y = rect.top;
				frame.width = rect.right - rect.left;
				frame.height = rect.bottom - rect.top;
			}
			return frame;
		}

		vec2i Win32Window::get_position() const {
			RECT rect = { NULL };
			vec2i pos;
			if(GetWindowRect(handle, &rect)) {
				pos.x = rect.left;
				pos.y = rect.top;
			}
			return pos;
		}

		vec2u Win32Window::get_size() const {
			RECT rect = {NULL};
			vec2u size;
			if (GetWindowRect(handle, &rect)) {
				size.x = rect.right - rect.left;
				size.y = rect.bottom - rect.top;
			}
			return size;
		}

		bool Win32Window::is_visible() const {
			return IsWindowVisible(handle);
		}

		void Win32Window::set_content_size(const vec2u & size) {
			RECT rect = {0, 0, static_cast<long>(size.x), static_cast<long>(size.y)};
			AdjustWindowRect(&rect, GetWindowLong(handle, GWL_STYLE), false);
			SetWindowPos(handle,
			             NULL,
			             0,
			             0,
			             rect.right - rect.left,
			             rect.bottom - rect.top,
			             SWP_NOMOVE | SWP_NOZORDER);
		}

		void Win32Window::set_frame(const recti & frame) {
			RECT rect = {
			    frame.x,
				frame.y,
				static_cast<long>(frame.width),
				static_cast<long>(frame.height)
			};
			//AdjustWindowRect(&rect, GetWindowLong(handle, GWL_STYLE), false);
			SetWindowPos(handle,
			             NULL,
			             rect.left,
			             rect.top,
			             rect.right - rect.left,
			             rect.bottom - rect.top,
			             SWP_NOZORDER);
		}

		void Win32Window::set_position(const vec2i & position) {
			SetWindowPos(handle, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}

		void Win32Window::set_size(const vec2u & size) {
			SetWindowPos(handle,
			             NULL,
			             0,
			             0,
			             static_cast<long>(size.x),
			             static_cast<long>(size.y),
			             SWP_NOMOVE | SWP_NOZORDER);
		}

		void Win32Window::set_visible(bool visible) {
			ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
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
