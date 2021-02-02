
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

			////////////////////////////////////////////////////////////
			/// @brief Tell wheter or not the window is visible onscreen
			///
			/// @return True if the window is visible otherwise false
			///
			////////////////////////////////////////////////////////////
			virtual bool isVisible() const = 0;
			virtual WindowHandle getHandle() const = 0;
			virtual void setVisible(bool visible) = 0;
			virtual void pool() = 0;
		};

	} // namespace internal

} // namespace ppr

#endif
