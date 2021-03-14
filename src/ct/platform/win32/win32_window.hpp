
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

			WindowHandle get_handle() const override;
			vec2u get_content_size() const override;
			recti get_frame() const override;
			vec2i get_position() const override;
			vec2u get_size() const override;
			bool is_visible() const override;

			void set_content_size(const vec2u & size) override;
			void set_frame(const recti & frame) override;
			void set_position(const vec2i & position) override;
			void set_size(const vec2u & size) override;
			void set_visible(bool visible) override;
			void dispose();

			static Win32Window * create(const WindowProperties & props);
		};

	} // namespace internal

} // namespace ct

#endif
