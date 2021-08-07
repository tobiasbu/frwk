
#ifndef _CHRONOTRIX_FRWK_X11_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_X11_WINDOW_HPP_

#include <ct/platform/window_impl.hpp>
#include <ct/platform/window_properties.hpp>
#include <ct/platform/x11/x11.hpp>

namespace ct {

	namespace internal {

		struct X11Borders{
			i32 left = 0;
			i32 right = 0;
			i32 top = 0;
			i32 bottom = 0;
		};

		class X11Window : public WindowImpl {
		private:
			Window handle;
			vec2u size;
			bool resizable;

		public:
			X11Window(Window handle);
			~X11Window();

			WindowHandle get_handle() const override;
			recti get_content_frame() const override;
			recti get_frame() const override;
			vec2i get_position() const override;
			vec2u get_size() const override;
			cstr get_title() const override;
			bool is_visible() const override;

			void set_frame(const recti & frame) override;
			void set_position(const vec2i & position) override;
			void set_size(const vec2u & size) override;
			void set_title(cstr title) override;
			void set_visible(bool visible) override;

			bool is_mapped() const;
			void dispose();

			static void process_event(XEvent * event);

			static X11Window * create(const WindowProperties & props);
		};

	} // namespace internal

} // namespace ct

#endif
