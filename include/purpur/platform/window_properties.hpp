
#ifndef _PURPURINA_FRWK_WINDOW_PROPERTIES_HPP_
#define _PURPURINA_FRWK_WINDOW_PROPERTIES_HPP_

#include <purpur/core/types.hpp>
#include <purpur/platform/window_style.hpp>

namespace ppr {

	struct PPR_PLATFORM_API WindowProperties {
		uint32 width;
		uint32 height;
		cstr title;
		uint32 style;

		WindowProperties() = default;
		WindowProperties(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default);
	};

}

#endif
