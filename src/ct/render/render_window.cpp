
#include <ct/render/render_window.hpp>
#include <ct/render/render_context.hpp>

namespace ct {

	RenderWindow::RenderWindow(Window && base_window, RenderContext * context)
	:
	context(context),
	Window(MOV(base_window))
	{}

	RenderWindowPtr create_render_window(uint32 width, uint32 height, cstr title, uint32 style, const ContextConfig & config) {

		WindowProperties props(
			width,
			height,
			title,
			style
		);

		return create_render_window(props, config);
	}

	RenderWindowPtr create_render_window(const WindowProperties & properties, const ContextConfig & config) {
		auto window = create_window(properties).release();
		auto context = RenderContext::create(window, config);

		auto ptr = std::make_unique<enable_make<RenderWindow>>(MOV(*window), context);
		// delete window;

		return ptr;
		// return  std::unique_ptr<RenderWindow>(renderWindow);
	}

} // namespace ct
