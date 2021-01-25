
#ifndef _PURPURINA_WINDOW_STYLE_HPP_
#define _PURPURINA_WINDOW_STYLE_HPP_

#include <purpur/core/config.hpp>

namespace ppr {

	namespace WindowStyle {
		////////////////////////////////////////////////////////////
		/// \ingroup purpurina_window
		/// \brief Window style mask
		///
		/// \see https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
		/// \see https://developer.apple.com/documentation/appkit/nswindowstylemask
		///
		////////////////////////////////////////////////////////////
		enum {
			////////////////////////////////////////////////////////////
			/// @brief No border and no title bar
			///
			///	- Win32:
			/// - MacOS: `NSWindowStyleMaskBorderless`
			////////////////////////////////////////////////////////////
			Borderless = 0,

			/**
			 * Title bar
			 *
			 * - Win32: `WS_CAPTION`
			 * - MacOS: `NSWindowStyleMaskTitled`
			 */
			Title = 1 << 0,

			/**
			 * Window can be resized by user
			 *
			 * - Win32: `WS_SIZEBOX`
			 * - MacOS: `NSWindowStyleMaskResizable`
			 */
			Resize = 1 << 1,

			////////////////////////////////////////////////////////////
			/// Close button
			///
			/// - Win32:
			/// - MacOS: NSWindowStyleMaskClosable
			////////////////////////////////////////////////////////////
			Close = 1 << 2,

			////////////////////////////////////////////////////////////
			/// Miniaturizable
			///
			/// - Win32: `WS_MAXIMIZEBOX` | `WS_MINIMIZEBOX`
			/// - MacOS: NSWindowStyleMaskMiniaturizable
			////////////////////////////////////////////////////////////
			Miniaturizable = 1 << 3,
		};

		constexpr uint32 Default = Title | Close | Resize | Miniaturizable;

		bool hasMask(const uint32 mask, const uint32 flag) {
			return mask & flag ? true : false;
		}
	}

}

#endif
