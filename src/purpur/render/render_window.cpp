
#include <purpur/platform/native_window_type.hpp>
#include <purpur/render/render_window.hpp>

namespace ppr {

	RenderWidow::RenderWidow(internal::NativeWindow * nativeWindow) : Window(nativeWindow) {}

	RenderWidow * RenderWidow::create() {
		// auto nativeWidow = new NativeWindowType(800, 600, "title", WindowStyle::Default);

		return nullptr;
	}

} // namespace ppr
