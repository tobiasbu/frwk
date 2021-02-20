
#include <ct/platform/window_style.hpp>

namespace ct {

	namespace WindowStyle {

		uint32 make(bool bordeless, bool titleBar, bool resizable, bool closable) {
			if (bordeless) {
				return Borderless;
			}
			uint32 style = 0U;
			if (titleBar) {
				style |= Title;
			}
			if (closable) {
				style |= Close;
			}
			if (resizable) {
				style |= Resize;
			}
			return style;
		}
	} // namespace WindowStyle

} // namespace ct
