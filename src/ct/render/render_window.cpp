
#include <ct/render/render_window.hpp>

namespace ct {

	RenderWidow::RenderWidow(WindowImpl * nativeWindow) : Window(nativeWindow) {}

	RenderWidow * RenderWidow::create() {
		return nullptr;
	}

} // namespace ct
