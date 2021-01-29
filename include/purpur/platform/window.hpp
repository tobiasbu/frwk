
#ifndef _PURPURINA_WINDOW_HPP_
#define _PURPURINA_WINDOW_HPP_

	#include <purpur/core/config.hpp>

	#include <purpur/platform/window_handle.hpp>
	#include <purpur/platform/window_style.hpp>
	#include <purpur/platform/export.hpp>

	namespace ppr {

		namespace internal {
			class NativeWindow;
		}

		class PURPURINA_PLATFORM_API Window {

			private:

				internal::NativeWindow * nativeWindow;

			public:

				Window(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default);
				~Window();

				bool isVisible();
				void setVisible(bool visible);
				void process();
				WindowHandle getHandle();

		};

	}

#endif
