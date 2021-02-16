
#include <purpur/render/render_window.hpp>

namespace ppr {

	RenderWidow::RenderWidow(WindowImpl * nativeWindow) : Window(nativeWindow) {}

	RenderWidow * RenderWidow::create() {
		return nullptr;
	}

} // namespace ppr
