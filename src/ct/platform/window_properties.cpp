

#include <ct/platform/window_properties.hpp>

namespace ct {

	WindowProperties::WindowProperties(u32 width, u32 height, cstr title, u32 style)
	: width(width),
	  height(height),
	  title(title),
	  style(style) {}

	
	bool WindowProperties::is_borderless() const {
		return style == WindowStyle::Borderless;
	}

	bool WindowProperties::is_resizable() const {
		return !!(style & WindowStyle::Resize);
	}

	bool WindowProperties::is_closable() const {
		return !!(style & WindowStyle::Close);
	}

	bool WindowProperties::has_title() const {
		return !!(style & WindowStyle::Title);
	}

	 
} // namespace ct
