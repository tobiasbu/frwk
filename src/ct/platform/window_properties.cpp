

#include <ct/platform/window_properties.hpp>

namespace ct {

	WindowProperties::WindowProperties(u32 width, u32 height, cstr title, u32 style)
	:
	width(width),
	height(height),
	title(title),
	style(style)
	{}
}
