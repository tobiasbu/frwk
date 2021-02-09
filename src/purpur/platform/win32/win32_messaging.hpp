
#ifndef _PURPURINA_FRWK_WIN32_MESSAGING_HPP_
#define _PURPURINA_FRWK_WIN32_MESSAGING_HPP_

#include <windows.h>

#include <purpur/core/utils/noncopyable.hpp>

namespace ppr {

	namespace internal {

		////////////////////////////////////////////////////////////
		/// @brief Internal Windows messaging transmiter
		///
		////////////////////////////////////////////////////////////
		class Win32Messaging : public NonCopyable {

			public:

			////////////////////////////////////////////////////////////
			/// @brief Main Window procedures.
			/// Listens to window events and dispatches to observers.
			///
			/// @param hWnd Handle to window
			/// @param uMsg Message identifier
			/// @param wParam First message parameter
			/// @param lParam Second message parameter
			///
			//////////////////////////////////////////////////////////
			static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			////////////////////////////////////////////////////////////
			/// @brief Non-constructible
			///
			////////////////////////////////////////////////////////////
			constexpr Win32Messaging() = delete;

		};

	}


}

#endif
