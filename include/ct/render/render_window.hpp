
#ifndef _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_RENDER_WINDOW_HPP_

#include <ct/platform/window_impl.hpp>
#include <ct/platform/window.hpp>
#include <ct/render/export.hpp>

namespace ct {

	class CT_RENDER_API RenderWidow : public Window {
	public:
		RenderWidow(WindowImpl * nativeWindow);
		static RenderWidow * create();
	};

} // namespace ct

#endif
