
#ifndef _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_

#include <ct/platform/window.hpp>
#include <ct/platform/context_config.hpp>
#include <ct/platform/export.hpp>

namespace ct {

	class RenderContext;
	class CT_PLATFORM_API RenderWindow : public Window {
		// friend CT_PLATFORM_API RenderWindowPtr create_render_window(u32 width,
		//                                                             u32 height,
		//                                                             cstr title,
		//                                                             u32 style,
		//                                                             const ContextConfig & config);
		// friend CT_PLATFORM_API RenderWindowPtr
		// create_render_window(const WindowProperties & properties, const ContextConfig & config);

	private:
		RenderContext * context;

	public:
		RenderWindow();
		RenderWindow(Window && base_window, RenderContext * context);

		void make_current();
		void swap_buffers();

		void create(u32 width,
					u32 height,
					cstr title,
					u32 style = WindowStyle::Default,
					const ContextConfig & config = ContextConfig());

		void create(const WindowProperties & properties,
	                const ContextConfig & config = ContextConfig());
	};
} // namespace ct

#endif
