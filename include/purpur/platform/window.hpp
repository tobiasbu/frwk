
#ifndef _PURPURINA_WINDOW_HPP_
#define _PURPURINA_WINDOW_HPP_

	#include <purpur/core/config.hpp>
	#include <purpur/platform/export.hpp>


	namespace ppr {

		namespace internal {
			class PlatformWindow;
		}

		class PURPURINA_PLATFORM_API Window {

			private:

				internal::PlatformWindow * platformWindow;

			public:

				Window(uint32 width, uint32 height, const char * title);
				~Window();

				bool isVisible();
				void setVisible(bool visible);
				void process();
				// WindowHandle getHandle() {};

		};

	}

#endif
