
#include <ct/platform/render_context.hpp>
#include <ct/platform/render_window.hpp>

namespace ct {

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

	RenderWindowPtr create_render_window(u32 width,
	                                     u32 height,
	                                     cstr title,
	                                     u32 style,
	                                     const ContextConfig & config) {
		WindowProperties props(width, height, title, style);

		return create_render_window(props, config);
	}

	RenderWindowPtr create_render_window(const WindowProperties & properties,
	                                     const ContextConfig & config) {
		auto window = create_window(properties).release();
		auto context = RenderContext::create(window, config);
		if (context == CT_NULLPTR) {
			return CT_NULLPTR;
		}
		// this is really bad solution
		// maybe we should move render window and context to platform module
		auto ptr = std::make_unique<enable_make<RenderWindow>>(MOV(*window), context);
		return ptr;
	}

} // namespace ct
