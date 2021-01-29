
#ifndef _PURPURINA_WIN32_WINDOW_HPP_
#define _PURPURINA_WIN32_WINDOW_HPP_

#include <windows.h>

#include <purpur/core/config.hpp>
#include <purpur/platform/native_window.hpp>

namespace ppr {

	namespace internal {

		class Win32Window : public NativeWindow {

			private:

				HWND handle;
				void onEvent(UINT message, WPARAM wParam, LPARAM lParam);

			public:

				Win32Window(uint32 width, uint32 height, cstr title, uint32 style);
				~Win32Window();

				void setVisible(bool visible);
				bool isVisible() const;
				HWND getHandle() const;
				void pool();
				void dispose();


		};

	}

}

	#endif
