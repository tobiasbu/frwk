
#ifndef _CHRONOTRIX_FRWK_X11_HPP_
#define _CHRONOTRIX_FRWK_X11_HPP_

#include <ct/config.hpp>
#include <ct/platform/window_properties.hpp>
#include <ct/math/vec.hpp>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xresource.h>
#include <X11/Xutil.h>

namespace ct {

	namespace x11 {

		struct Atoms {
			// string atoms
			Atom X11_NULL;
			Atom UTF8_STRING;

			// ICCCM, EWMH and Motif window property atoms
			Atom WM_PROTOCOLS;

			// Window Manager SHOULD honor _NET_WM_STATE whenever a withdrawn window requests to be
			// mapped
			Atom WM_STATE;

			// Close event
			Atom WM_DELETE_WINDOW;

			// This property MUST be set by the Window Manager to indicate which hints it supports
			Atom NET_SUPPORTED;

			// Window Manager MUST set this property on the root window to be the ID of a
			// child window created by himself, to indicate that a compliant window
			// manager is active
			Atom NET_SUPPORTING_WM_CHECK;

			// An array of 32bit packed CARDINAL ARGB of possible icons
			Atom NET_WM_ICON;

			// Determine if the Client is still processing X events
			Atom NET_WM_PING;
			Atom NET_WM_PID;
			Atom NET_WM_NAME;
			Atom NET_WM_ICON_NAME;
			Atom NET_WM_BYPASS_COMPOSITOR;
			Atom NET_WM_WINDOW_OPACITY;
			Atom MOTIF_WM_HINTS;

			// EWMH atoms
			Atom NET_WM_STATE;
			Atom NET_WM_STATE_ABOVE;
			Atom NET_WM_STATE_FULLSCREEN;
			Atom NET_WM_STATE_MAXIMIZED_VERT;
			Atom NET_WM_STATE_MAXIMIZED_HORZ;
			Atom NET_WM_STATE_DEMANDS_ATTENTION;
			Atom NET_WM_FULLSCREEN_MONITORS;
			Atom NET_WM_WINDOW_TYPE;
			Atom NET_WM_WINDOW_TYPE_NORMAL;
			Atom NET_WORKAREA;
			Atom NET_CURRENT_DESKTOP;
			Atom NET_ACTIVE_WINDOW;
			Atom NET_FRAME_EXTENTS;
			Atom NET_REQUEST_FRAME_EXTENTS;
			Atom NET_WM_CM_Sn; // Manager Selection
		};

		extern Display * display;
		extern u32 screen;
		extern XID root;
		extern XContext context;
		extern Atoms atoms;
		extern i32 last_error_code;

		i32 get_window_property(Window window, Atom property, Atom type, u8 ** value);

		void catch_error_handler();
		void release_error_handler();

		bool create_window(const WindowProperties & props, Visual* visual, i32 depth, Window & result);
		void update_window_normal_hints(const Window & handle, const vec2u & size);
		void save_window_context(const Window & handle, XPointer window_ptr);


	} // namespace x11

} // namespace ct

#endif
