
#include <windows.h>

#include <ct/platform/detail/win32_detail.hpp>
#include <ct/render/win32/win32_internal.hpp>

namespace ct {

	namespace internal {

		HWND helper_window = CT_NULLPTR;

		bool create_helper_window() {
			if (helper_window) {
				return true;
			}

			helper_window = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,
			                                __CT_WNDCLASSNAME,
			                                L"CT Helper window",
			                                WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			                                0,
			                                0,
			                                1,
			                                1,
			                                NULL,
			                                NULL,
			                                GetModuleHandleW(NULL),
			                                NULL);

			if (!helper_window) {
				return false;
			}

			ShowWindow(helper_window, SW_HIDE);

			MSG msg;
			while (PeekMessageW(&msg, helper_window, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}

			return true;
		}

		void destroy_helper_window() {
			if (helper_window) {
				DestroyWindow(helper_window);
				helper_window = CT_NULLPTR;
			}
		}

		HWND get_helper_window() {
			return helper_window;
		}
	} // namespace internal

} // namespace ct
