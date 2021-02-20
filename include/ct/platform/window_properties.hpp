
#ifndef _CHRONOTRIX_FRWK_WINDOW_PROPERTIES_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_PROPERTIES_HPP_

#include <ct/core/types.hpp>
#include <ct/platform/window_style.hpp>

namespace ct {

	struct CT_PLATFORM_API WindowProperties {
		uint32 width;
		uint32 height;
		cstr title;
		uint32 style;

		WindowProperties() = default;
		WindowProperties(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default);
	};

}

#endif
