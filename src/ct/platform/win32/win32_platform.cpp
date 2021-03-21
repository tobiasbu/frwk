
#include <strsafe.h>
#include <windows.h>

#include <ct/platform/detail/win32_detail.hpp>
#include <ct/platform/platform.hpp>
#include <ct/platform/win32/win32_messaging.hpp>
#include <ct/platform/win32/win32_window.hpp>

namespace ct {

	namespace Platform {

		namespace detail {

			bool initialized = false;

			////////////////////////////////////////////////////////////
			/// \brief Register Window class
			////////////////////////////////////////////////////////////
			bool register_windows_class() {
				WNDCLASSEXW wndclass;
				wndclass.cbSize = sizeof(wndclass); // The size, in bytes, of this structure
				wndclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC; // class style(s)
				wndclass.lpfnWndProc = (WNDPROC)internal::Win32Messaging::MainWndProc; // A pointer to the window procedure.

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
				wndclass.lpszClassName = __CT_WNDCLASSNAME;
				wndclass.lpszMenuName = NULL;
				if (!RegisterClassExW(&wndclass)) {
					return false;
				}
				return true;
			}

			// https://docs.microsoft.com/en-us/windows/win32/hidpi/setting-the-default-dpi-awareness-for-a-process
			// bool set_process_dpi_awareness() {

			// }

			void get_last_error() {
				// Retrieve the system error message for the last-error code
				LPTSTR lpszFunction = (char*)"GetProcessId";
				LPVOID lpMsgBuf;
				LPVOID lpDisplayBuf;
				DWORD dw = GetLastError();

				// clang-format off
				FormatMessage(
					FORMAT_MESSAGE_ALLOCATE_BUFFER |
					FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					dw,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR) &lpMsgBuf,
					0, NULL );

				// Display the error message and exit the process

				lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
					(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
				StringCchPrintf((LPTSTR)lpDisplayBuf,
					LocalSize(lpDisplayBuf) / sizeof(TCHAR),
					TEXT("%s failed with error %d: %s"),
					lpszFunction, dw, lpMsgBuf);
				MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
				// clang-format on

				LocalFree(lpMsgBuf);
				LocalFree(lpDisplayBuf);
			}

		} // namespace detail

		bool init() {
			if (detail::initialized) {
				return true;
			}

			if (!detail::register_windows_class()) {
				// TODO(@tobiasbu): error log
				return false;
			}

			return (detail::initialized = true);
		}

		bool terminate() {
			if (!detail::initialized) {
				return true;
			}

			if (!UnregisterClassW(__CT_WNDCLASSNAME, GetModuleHandleW(NULL))) {
				// TODO(@tobiasbu): error log
				detail::get_last_error();
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
