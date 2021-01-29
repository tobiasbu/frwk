
#ifndef _PURPURINA_FRWK_NATIVE_WINDOW_HPP_
#define _PURPURINA_FRWK_NATIVE_WINDOW_HPP_

#include <purpur/platform/window_handle.hpp>

namespace ppr {

	namespace internal {

		////////////////////////////////////////////////////////////
		/// \brief Represents abstraction for OS-specifc window class
		///
		////////////////////////////////////////////////////////////
		class NativeWindow {

			public:

				virtual ~NativeWindow() {}
				virtual bool isVisible() const = 0;
				virtual WindowHandle getHandle() const = 0;
				virtual void setVisible(bool visible) = 0;
				// virtual PlatformWindow * create(int32 width, int32 height, cstr title, uint32 style) const = 0;
				virtual void pool() = 0;


		};

	}

}

#endif
