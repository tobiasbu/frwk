
#ifndef _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_

#include <ct/platform/window.hpp>
#include <ct/render/context_config.hpp>
#include <ct/render/export.hpp>


namespace ct {

	class RenderContext;
	class RenderWindow;
	using RenderWindowPtr = std::unique_ptr<RenderWindow>;

	class CT_RENDER_API RenderWindow : public Window {

		friend CT_RENDER_API RenderWindowPtr create_render_window(uint32 width, uint32 height, cstr title, uint32 style, const ContextConfig & config);
		friend CT_RENDER_API RenderWindowPtr create_render_window(const WindowProperties & properties, const ContextConfig & config);

	private:

		RenderContext * context;

	public:
		RenderWindow() = delete;
		RenderWindow(Window && base_window, RenderContext * context);

		void make_current();
		void swap_buffers();

		static RenderWindow* create(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default, const ContextConfig & config = ContextConfig());
	};



	CT_RENDER_API RenderWindowPtr create_render_window(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default, const ContextConfig & config = ContextConfig());
	CT_RENDER_API RenderWindowPtr create_render_window(const WindowProperties & properties, const ContextConfig & config = ContextConfig());

} // namespace ct

#endif
