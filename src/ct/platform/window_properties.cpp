

#include <ct/platform/window_properties.hpp>

namespace ct {

	WindowProperties::WindowProperties(uint32 width, uint32 height, cstr title, uint32 style)
	:
	width(width),
	height(height),
	title(title),
	style(style)
	{}
}
