
#ifndef _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_

#include <ct/platform/window.hpp>

#include <ct/render/context_config.hpp>
#include <ct/render/export.hpp>


namespace ct {



	class CT_RENDER_API RenderWidow : public Window {
	protected:
		RenderWidow(WindowImpl * nativeWindow);
	};

	using RenderWindowPtr = std::unique_ptr<RenderWidow>;

	CT_RENDER_API RenderWindowPtr create_render_window(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default, const ContextConfig & config = ContextConfig());
	CT_RENDER_API RenderWindowPtr create_render_window(const WindowProperties & properties, const ContextConfig & config = ContextConfig());

} // namespace ct

#endif
