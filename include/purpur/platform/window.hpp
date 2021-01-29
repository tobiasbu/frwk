
#ifndef _PURPURINA_FRWK_WINDOW_HPP_
#define _PURPURINA_FRWK_WINDOW_HPP_

#include <purpur/core/types.hpp>
#include <purpur/core/utils/noncopyable.hpp>

#include <purpur/platform/window_handle.hpp>
// #include <purpur/platform/window_style.hpp>
#include <purpur/platform/export.hpp>

namespace ppr {

	namespace internal {
		class NativeWindow;
	}

	class PPR_PLATFORM_API Window : public NonCopyable {

		protected:

			internal::NativeWindow * nativeWindow;

		public:

			Window(internal::NativeWindow * nativeWindow);
			Window(uint32 width, uint32 height, cstr title, uint32 style);
			~Window();

			bool isVisible();
			void setVisible(bool visible);
			void process();
			WindowHandle getHandle();

			static void create();

	};

}

#endif
