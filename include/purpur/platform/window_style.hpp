
#ifndef _PURPURINA_FRWK_WINDOW_STYLE_HPP_
#define _PURPURINA_FRWK_WINDOW_STYLE_HPP_

#include <purpur/core/types.hpp>
#include <purpur/platform/export.hpp>

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
		enum : uint32
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

			////////////////////////////////////////////////////////////
			/// @brief Miniaturizable
			///
			/// - Win32: `WS_MINIMIZEBOX` | `WS_SYSMENU`
			/// - MacOS: NSWindowStyleMaskMiniaturizable
			////////////////////////////////////////////////////////////
			Minimize = 1u << 3u,
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

		PPR_PLATFORM_API uint32
		make(bool bordeless, bool titleBar, bool resizable, bool closable, bool minimizable);
	}; // namespace WindowStyle

} // namespace ppr

#endif
