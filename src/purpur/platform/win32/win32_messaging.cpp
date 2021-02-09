
#include <purpur/platform/win32/win32_messaging.hpp>
#include <purpur/platform/win32/win32_window.hpp>

namespace ppr {

	namespace internal {

		LRESULT CALLBACK Win32Messaging::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			// if (uMsg == WM_CREATE) {
			// 	LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;
			// 	SetWindowLongPtrW(hWnd, GWLP_USERDATA, window);
			// }

			HANDLE windowProp = GetPropW(hWnd, L"PPR");

			// Get the Window instance corresponding to the window handle
			internal::Win32Window * window = windowProp ? (internal::Win32Window *)windowProp : NULL;

			if (window) {
				window->onEvent(uMsg, wParam, lParam);
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

	}

}
