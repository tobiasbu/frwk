
#ifndef _PURPURINA_PLATFORM_WINDOW_HPP_
#define _PURPURINA_PLATFORM_WINDOW_HPP_

#include <purpur/core/config.hpp>

	namespace ppr {

		namespace internal {

			struct Vector2i {
				int x;
				int y;
			};

			////////////////////////////////////////////////////////////
			/// \brief Represents abstraction for OS-specifc window class
			///
			////////////////////////////////////////////////////////////
			class PlatformWindow {

				public:

					// virtual WindowHandle getHandle() {};
					virtual ~PlatformWindow() {}
					virtual PlatformWindow * create(uint32 width, uint32 height, cstr title, uint32 style) const = 0;
					virtual bool isVisible() = 0;
					virtual void setVisible(bool visible) = 0;
					virtual void pool() = 0;


			};

		}

	}

#endif
