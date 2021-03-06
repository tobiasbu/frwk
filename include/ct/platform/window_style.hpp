
#ifndef _CHRONOTRIX_FRWK_WINDOW_STYLE_HPP_
	#define _CHRONOTRIX_FRWK_WINDOW_STYLE_HPP_

	#include <ct/config/types.hpp>
	#include <ct/platform/export.hpp>

namespace ct {

	////////////////////////////////////////////////////////////
	/// @brief Window style mask
	///
	////////////////////////////////////////////////////////////
	namespace WindowStyle {
		enum : u32
		{
			////////////////////////////////////////////////////////////
			/// @brief No border and no title bar
			///
			///	- Win32: `WS_POPUP`
			/// - MacOS: `NSWindowStyleMaskBorderless`
			////////////////////////////////////////////////////////////
			Borderless = 0u,

			/**
			 * @brief Title bar
			 *
			 * @li Win32: `WS_CAPTION`
			 * @li MacOS: `NSWindowStyleMaskTitled`
			 */
			Title = 1u << 0u,

			/**
			 * Window can be resized by user
			 *
			 * - Win32: `WS_THICKFRAME` | `WS_MAXIMIZEBOX` | `WS_SYSMENU`
			 * - MacOS: `NSWindowStyleMaskResizable`
			 */
			Resize = 1u << 1u,

			////////////////////////////////////////////////////////////
			/// @brief Close button
			///
			/// - Win32: `WS_SYSMENU`
			/// - MacOS: NSWindowStyleMaskClosable
			////////////////////////////////////////////////////////////
			Close = 1u << 2u,
		};

		/**
		 * @brief Default window style
		 *
		 * The default style contains:
		 * @code
		 * 	auto my_win_style = Title | Close | Resize;
		 * @endcode
		 */
		constexpr u32 Default = Title | Close | Resize;

		////////////////////////////////////////////////////////////
		/// @brief Helper to create custom WindowStyle
		///
		/// @param bordeless Should bordeless
		/// @param titleBar Should have title bar
		/// @param resizable Should be resizable
		/// @param closable Should be closable
		/// @return WindowStyle
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API u32 make(bool bordeless, bool titleBar, bool resizable, bool closable);

	}; // namespace WindowStyle

} // namespace ct

#endif

////////////////////////////////////////////////////////////
/// @ingroup platform
///
/// @see https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
/// @see https://developer.apple.com/documentation/appkit/nswindowstylemask
///
////////////////////////////////////////////////////////////
