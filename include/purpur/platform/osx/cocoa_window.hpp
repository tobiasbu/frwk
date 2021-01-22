
#ifndef _PURPURINA_COCOA_WINDOW_HPP_
#define _PURPURINA_COCOA_WINDOW_HPP_

#include <purpur/core/config.hpp>

#include <purpur/platform/platform_window.hpp>

	namespace ppr {

		namespace internal {

			class CocoaWindow : PlatformWindow {

				////////////////////////////////////////////////////////////
				/// \brief Constructs the window instance
				///
				////////////////////////////////////////////////////////////
				CocoaWindow(uint32 width, uint32 height, cstr title);

				////////////////////////////////////////////////////////////
				/// \brief Destructor
				///
				////////////////////////////////////////////////////////////
				~CocoaWindow();
			};

		}

	}

#endif
