
#ifndef _PURPURINA_FRWK_RENDER_WINDOW_HPP_
#define _PURPURINA_FRWK_RENDER_WINDOW_HPP_

#include <purpur/platform/window_impl.hpp>
#include <purpur/platform/window.hpp>
#include <purpur/render/export.hpp>

namespace ppr {

	class PPR_RENDER_API RenderWidow : public Window {
	public:
		RenderWidow(WindowImpl * nativeWindow);
		static RenderWidow * create();
	};

} // namespace ppr

#endif
