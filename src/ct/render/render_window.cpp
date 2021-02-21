
#include <ct/render/render_window.hpp>

namespace ct {

	RenderWidow::RenderWidow(WindowImpl * nativeWindow) : Window(nativeWindow) {}


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
		// auto impl = WindowImplType::create(props);
		// return std::make_unique<enable_make<RenderWidow>>(impl);
		return nullptr;
	}

} // namespace ct
