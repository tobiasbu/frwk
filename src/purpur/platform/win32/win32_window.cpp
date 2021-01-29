
#include <purpur/platform/window_style.hpp>

#include <purpur/platform/win32/win32_platform.hpp>
#include <purpur/platform/win32/win32_window.hpp>

#include <iostream>

namespace ppr {

	namespace internal {


		////////////////////////////////////////////////////////////
		/// Internal Apis
		////////////////////////////////////////////////////////////

		int windowCount = 0;

		////////////////////////////////////////////////////////////
		/// \brief Main Window procedures.
		/// Listens to window events and dispatches to observers.
		///
		/// \param hWnd Handle to window
		/// \param uMsg Message identifier
		/// \param wParam First message parameter
		/// \param lParam Second message parameter
		///
		//////////////////////////////////////////////////////////
		LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)  {
			// if (uMsg == WM_CREATE) {
			// 	LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;
			// 	SetWindowLongPtrW(hWnd, GWLP_USERDATA, window);
			// }

			HANDLE windowProp = GetPropW(hWnd, L"PPR");

			// Get the Window instance corresponding to the window handle
			Win32Window* window = windowProp ? (Win32Window*)windowProp : NULL;

			if (window) {
				// window->onEvent(uMsg, wParam, lParam);
			}

			// Prevents Windows to detroy the window automatically
			if (uMsg == WM_CLOSE) {
				// return 0;
			}

			// Prevents focus loss from Alt and F10 keys
			if (uMsg == WM_SYSCOMMAND && wParam == SC_KEYMENU) {
				return 0;
			}

			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
		}

		////////////////////////////////////////////////////////////
		/// \brief Register Window class
		////////////////////////////////////////////////////////////
		bool registerWindowsClass() {
			WNDCLASSEXW wndclass;
			wndclass.cbSize = sizeof(wndclass); // The size, in bytes, of this structure
			wndclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC; // class style(s)  // ;
			wndclass.lpfnWndProc = (WNDPROC)MainWndProc; // A pointer to the window procedure.
			wndclass.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
			wndclass.cbWndExtra = 0; // The number of extra bytes to allocate following the window instance.
			wndclass.hInstance = GetModuleHandleW(NULL); // A handle to the instance that contains the window procedure for the class.
			wndclass.hIcon = NULL; // class icon.
			wndclass.hIconSm = NULL;
			wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // class cursor.
			wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // class background brush.
			// wndclass.lpszMenuName = __PPR_WNDCLASSNAME; //  specifies the resource name of the class menu, as the name appears in the resource file
			wndclass.lpszClassName = __PPR_WNDCLASSNAME;
			wndclass.lpszMenuName = NULL;
			if (!RegisterClassExW(&wndclass)) {
				std::cerr << "Could no register window class" << std::endl;
				return false;
			}
			return true;
		}



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

		Win32Window::Win32Window(uint32 width, uint32 height, cstr title, uint32 style) {

			// Register window class only for first window
			if (windowCount == 0) {
				if (!registerWindowsClass()) {
					return;
				}
			}


			bool isFullscreen = false;

			// Retrieves a handle to a device context (DC) for the client area of a specified window or for the entire screen
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

			const wchar_t* titleWchar = toWchar(title);
			if (!titleWchar) {
				std::cerr << "Invalid title" << std::endl;
				return;
			}

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

			if (!handle) {
				std::cerr << "Could no create window" << std::endl;
				return;
				/* ShowWindow(handle, 1);
				UpdateWindow(handle);*/
			}

			// if (style == 0) {
			// 	SetWindowLong(handle, GWL_STYLE, 0 );
			// }

			SetPropW(handle, L"PPR", this);

			windowCount += 1;

		}

		Win32Window::~Win32Window() {
			dispose();

			if (windowCount == 0) {
				UnregisterClassW(__PPR_WNDCLASSNAME, GetModuleHandleW(NULL));
			}
		}

		void Win32Window::setVisible(bool visible) {
			ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
		}

		HWND Win32Window::getHandle() const {
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
				std::cout << "Window disposed" << std::endl;
				RemovePropW(handle, L"PPR");
        		DestroyWindow(handle);
				handle = nullptr;

				windowCount -= 1;

			}
		}





		// LRESULT CALLBACK Win32Window::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	}
}
