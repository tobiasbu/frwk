
#include <ct/platform/render_context.hpp>
#include <ct/platform/render_window.hpp>

namespace ct {

	RenderWindow::RenderWindow(): context(CT_NULLPTR) {}

	RenderWindow::RenderWindow(Window && base_window, RenderContext * context)
	: context(context),
	  Window(MOV(base_window)) {}

	void RenderWindow::make_current() {
		if (context) {
			context->make_current();
		}
	}

	void RenderWindow::swap_buffers() {
		if (context) {
			context->swap_buffers();
		}
	}

	void RenderWindow::create(u32 width,
				u32 height,
				cstr title,
				u32 style,
				const ContextConfig & config) {				
		WindowProperties props(width, height, title, style);
		create(props, config);
	}

	void RenderWindow::create(const WindowProperties & properties,
				const ContextConfig & config) {
		auto impl = create_window_impl(properties);
		this->context = RenderContext::create(impl, config);
		this->impl = impl;
		// if (context == CT_NULLPTR) {
		// 	return;
		// }
		
		
	}

} // namespace ct
