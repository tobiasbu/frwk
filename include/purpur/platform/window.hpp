
#ifndef _PURPURINA_WINDOW_HPP_
#define _PURPURINA_WINDOW_HPP_

	#include <purpur/platform/platform_window.hpp>

	namespace ppr {

		class Window {

			private:

				internal::PlatformWindow * nativeWindow;

			public:

				Window();
				~Window();

		};

	}

#endif
