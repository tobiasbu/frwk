
#ifndef _PURPURINA_WINDOW_STYLE_HPP_
#define _PURPURINA_WINDOW_STYLE_HPP_

#include <purpur/core/config.hpp>

namespace ppr {

	////////////////////////////////////////////////////////////
	/// \ingroup purpurina_window
	/// \brief Window style mask
	///
	/// \see https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
	/// \see https://developer.apple.com/documentation/appkit/nswindowstylemask
	///
	////////////////////////////////////////////////////////////
	namespace WindowStyle {
		enum {
			////////////////////////////////////////////////////////////
			/// @brief No border and no title bar
			///
			///	- Win32: `WS_POPUP`
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
			 * - Win32: `WS_THICKFRAME` | `WS_MAXIMIZEBOX` | `WS_SYSMENU`
			 * - MacOS: `NSWindowStyleMaskResizable`
			 */
			Resize = 1 << 1,

			////////////////////////////////////////////////////////////
			/// Close button
			///
			/// - Win32: `WS_SYSMENU`
			/// - MacOS: NSWindowStyleMaskClosable
			////////////////////////////////////////////////////////////
			Close = 1 << 2,

			////////////////////////////////////////////////////////////
			/// Miniaturizable
			///
			/// - Win32: `WS_MINIMIZEBOX` | `WS_SYSMENU`
			/// - MacOS: NSWindowStyleMaskMiniaturizable
			////////////////////////////////////////////////////////////
			Minimize = 1 << 3,
		};

		/**
		 * @brief Default window style
		 *
		 * The default style contains:
		 * @code
		 * 		Title | Close | Resize | Minimize
		 * @endcode
		 */
		constexpr uint32 Default = Title | Close | Resize | Minimize;

		uint32 make(bool bordeless, bool titleBar, bool resizable, bool closable, bool minimizable) {
			if (bordeless) {
				return Borderless;
			}
			uint32 style = 0;
			if (titleBar) {
				style |= Title;
			}
			if (closable) {
				style |= Close;
			}
			if (resizable) {
				style |= Resize;
			}
			if (minimizable) {
				style |= Minimize;
			}
			return style;
		}
	}

}

#endif
