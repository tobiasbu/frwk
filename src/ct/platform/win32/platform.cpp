

#include <windows.h>

#include <ct/platform/platform.hpp>
#include <ct/platform/win32/win32_detail.hpp>
#include <ct/platform/win32/win32_messaging.hpp>
#include <ct/platform/win32/win32_window.hpp>


namespace ct {

	namespace Platform {

		namespace detail {

			bool initialized = false;

			////////////////////////////////////////////////////////////
			/// \brief Register Window class
			////////////////////////////////////////////////////////////
			bool registerWindowsClass() {
				WNDCLASSEXW wndclass;
				wndclass.cbSize = sizeof(wndclass); // The size, in bytes, of this structure
				wndclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC; // class style(s)
				wndclass.lpfnWndProc = (WNDPROC)
				    internal::Win32Messaging::MainWndProc; // A pointer to the window procedure.

				// clang-format off
				wndclass.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
				wndclass.cbWndExtra = 0; // The number of extra bytes to allocate following the window instance.
				wndclass.hInstance = GetModuleHandleW(NULL); // A handle to the instance that contains the window procedure for the class.
				// clang-format on

				wndclass.hIcon = NULL; // class icon.
				wndclass.hIconSm = NULL;
				wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);      // class cursor.
				wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // class background brush.

				// specifies the resource name of the class menu, as the name appears in the
				// resource file wndclass.lpszMenuName = __CT_WNDCLASSNAME;
				wndclass.lpszClassName = __CT_WNDCLASSNAME;
				wndclass.lpszMenuName = NULL;
				return RegisterClassExW(&wndclass);
			}
		} // namespace detail

		bool init() {
			if (detail::initialized) {
				return true;
			}

			if (!detail::registerWindowsClass()) {
				return false;
			}

			return (detail::initialized = true);
		}

		bool terminate() {
			if (!detail::initialized) {
				return true;
			}

			if (!UnregisterClassW(__CT_WNDCLASSNAME, GetModuleHandleW(NULL))) {
				return false;
			}

			detail::initialized = false;

			return true;
		}

		void poll_events() {
			if (!detail::initialized) {
				return;
			}

			MSG message;
			while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&message);
				DispatchMessageW(&message);
			}
		}

	} // namespace Platform
} // namespace ct
