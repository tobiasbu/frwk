
#ifndef _PURPURINA_FRWK_WIN32_WINDOW_HPP_
#define _PURPURINA_FRWK_WIN32_WINDOW_HPP_

#include <purpur/core/types.hpp>
#include <purpur/platform/native_window.hpp>
#include <windows.h>

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
			WindowHandle getHandle() const;
			void pool();
			void dispose();
		};

	} // namespace internal

} // namespace ppr

#endif
