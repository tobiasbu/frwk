
#ifndef _CHRONOTRIX_FRWK_WIN32_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_WIN32_WINDOW_HPP_

#include <windows.h>

#include <ct/config/types.hpp>
#include <ct/platform/window_impl.hpp>
#include <ct/platform/window_properties.hpp>

namespace ct {

	namespace internal {

		class Win32Messaging;

		class Win32Window : public WindowImpl {
			friend class Win32Messaging;

		private:
			HWND handle;
			void on_event(UINT message, WPARAM wParam, LPARAM lParam);

		public:
			Win32Window(HWND handle);
			~Win32Window();

			void set_visible(bool visible) override;
			bool is_visible() const override;
			WindowHandle get_handle() const override;
			void dispose();

			static Win32Window * create(const WindowProperties & props);
		};

	} // namespace internal

} // namespace ct

#endif
