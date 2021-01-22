
#ifndef _PURPURINA_PLATFORM_WINDOW_HPP_
#define _PURPURINA_PLATFORM_WINDOW_HPP_

	namespace ppr {

		namespace internal {

			struct Vector2i {
				int x;
				int y;
			};

			typedef int WindowHandle;

			////////////////////////////////////////////////////////////
			/// \brief Represents abstraction for OS-specifc window class
			///
			////////////////////////////////////////////////////////////
			class PlatformWindow {

				public:

					virtual ~PlatformWindow();
					virtual WindowHandle getHandle() {};
					virtual bool isVisible() = 0;
					virtual void setVisible(bool visible) = 0;

			};

		}

	}

#endif
