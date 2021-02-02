
#include <purpur/platform/window_style.hpp>

namespace ppr {

	namespace WindowStyle {

		uint32
		make(bool bordeless, bool titleBar, bool resizable, bool closable, bool minimizable) {
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
			if (minimizable) {
				style |= Minimize;
			}
			return style;
		}
	}// namespace WindowStyle

}// namespace ppr
