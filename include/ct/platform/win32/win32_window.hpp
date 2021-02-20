
#ifndef _CHRONOTRIX_FRWK_WIN32_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_WIN32_WINDOW_HPP_

#include <windows.h>

#include <ct/core/types.hpp>
#include <ct/platform/window_impl.hpp>
#include <ct/platform/window_properties.hpp>

namespace ct {

	namespace internal {

		class Win32Messaging;

		class Win32Window : public WindowImpl {
			friend class Win32Messaging;

		private:
			HWND handle;
			void onEvent(UINT message, WPARAM wParam, LPARAM lParam);

		public:
			Win32Window(HWND handle);
			~Win32Window();

			void setVisible(bool visible) override;
			bool isVisible() const override;
			WindowHandle getHandle() const override;
			void dispose();

			static Win32Window * create(const WindowProperties & props);
		};

	} // namespace internal

} // namespace ct

#endif