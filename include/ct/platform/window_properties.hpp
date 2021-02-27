
#ifndef _CHRONOTRIX_FRWK_WINDOW_PROPERTIES_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_PROPERTIES_HPP_

#include <ct/core/types.hpp>
#include <ct/platform/window_style.hpp>

namespace ct {

	struct CT_PLATFORM_API WindowProperties {
		u32 width;
		u32 height;
		cstr title;
		u32 style;

		WindowProperties() = default;
		WindowProperties(u32 width, u32 height, cstr title, u32 style = WindowStyle::Default);
	};

}

#endif
