

#include <map>

#include <ct/config.hpp>
#include <ct/platform/platform.hpp>
#include <ct/platform/x11/x11_window.hpp>
#include <ct/platform/x11/x11.hpp>

namespace ct {

	namespace Platform {

		Atom get_atom(cstr atomName, bool only_if_exists = false) {
			return XInternAtom(x11::display, atomName, only_if_exists ? True : False);
		}

		/// Check if Extended Window Manager hints are supported
		void check_ewmh_support() {
			if (x11::ewmh_checked) {
				return;
			}

			x11::ewmh_checked = true;

			// Check NET_SUPPORTED and NET_SUPPORTING_WM_CHECK exists
			x11::Atoms & atoms = x11::atoms;
			if (!atoms.NET_SUPPORTED || !atoms.NET_SUPPORTING_WM_CHECK) {
				return;
			}

			// check the _NET_SUPPORTING_WM_CHECK property on the root window
			Window * windowFromRoot = NULL;
			if (!x11::get_window_property(
			        x11::root, atoms.NET_SUPPORTING_WM_CHECK, XA_WINDOW, (u8 **)&windowFromRoot)) {
				return;
			}

			x11::catch_error_handler();

			Window * windowFromChild = NULL;
			if (!x11::get_window_property(*windowFromRoot,
			                              atoms.NET_SUPPORTING_WM_CHECK,
			                              XA_WINDOW,
			                              (u8 **)&windowFromChild)) {
				XFree(windowFromChild);
				return;
			}

			x11::release_error_handler();

			// Conforming window managers should return the same window for both queries
			bool isTheSameWindow = *windowFromRoot == *windowFromChild;

			XFree(windowFromChild);
			XFree(windowFromRoot);

			if (!isTheSameWindow) {
				return;
			}

			x11::ewmh_supported = true;

			// try to get window manager name for workarounds
			atoms.NET_WM_STATE = get_atom("_NET_WM_NAME", true);
			atoms.NET_WM_STATE_ABOVE = get_atom("_NET_WM_STATE_ABOVE", true);
			atoms.NET_WM_STATE_FULLSCREEN = get_atom("_NET_WM_STATE_FULLSCREEN", true);
			atoms.NET_WM_STATE_MAXIMIZED_VERT = get_atom("_NET_WM_STATE_MAXIMIZED_VERT", true);
			atoms.NET_WM_STATE_MAXIMIZED_HORZ = get_atom("_NET_WM_STATE_MAXIMIZED_HORZ", true);
			atoms.NET_WM_STATE_DEMANDS_ATTENTION =
			    get_atom("_NET_WM_STATE_DEMANDS_ATTENTION", true);
			atoms.NET_WM_FULLSCREEN_MONITORS = get_atom("_NET_WM_FULLSCREEN_MONITORS", true);
			atoms.NET_WM_WINDOW_TYPE = get_atom("_NET_WM_WINDOW_TYPE", true);
			atoms.NET_WM_WINDOW_TYPE_NORMAL = get_atom("_NET_WM_WINDOW_TYPE_NORMAL", true);
			atoms.NET_WORKAREA = get_atom("_NET_WORKAREA", true);
			atoms.NET_CURRENT_DESKTOP = get_atom("_NET_CURRENT_DESKTOP", true);
			atoms.NET_ACTIVE_WINDOW = get_atom("_NET_ACTIVE_WINDOW", true);
			atoms.NET_FRAME_EXTENTS = get_atom("_NET_FRAME_EXTENTS", true);
			atoms.NET_REQUEST_FRAME_EXTENTS = get_atom("_NET_REQUEST_FRAME_EXTENTS", true);
		}

		bool init() {
			if (x11::display != NULL) {
				return true;
			}

			// The XOpenDisplay() function returns a Display structure that serves as the
			// connection to the X server and that contains all the information about that X
			// server.
			Display * display = XOpenDisplay(NULL);

			if (!display) {
				return false;
			}
			x11::display = display;

			// retrieve the screen number in applications that will use only a single screen
			x11::screen = DefaultScreen(display);

			// return root window  that need a drawable of a particular screen and for creating
			// top-level windows
			x11::root = RootWindow(display, x11::screen);

			// Create context
			x11::context = XUniqueContext();

			// Setup base xtensions
			x11::Atoms & atoms = x11::atoms;

			// String format atoms
			atoms.X11_NULL = get_atom("NULL");
			atoms.UTF8_STRING = get_atom("UTF8_STRING");

			// ICCCM, EWMH and Motif window property atoms

			// Check required atoms for EWMH
			atoms.NET_SUPPORTED = get_atom("_NET_SUPPORTED", true);
			atoms.NET_SUPPORTING_WM_CHECK = get_atom("_NET_SUPPORTING_WM_CHECK", true);

			atoms.WM_PROTOCOLS = get_atom("WM_PROTOCOLS");
			atoms.WM_STATE = get_atom("WM_STATE");
			atoms.WM_DELETE_WINDOW = get_atom("WM_DELETE_WINDOW");
			atoms.NET_WM_ICON = get_atom("_NET_WM_ICON");
			atoms.NET_WM_PING = get_atom("_NET_WM_PING");
			atoms.NET_WM_PID = get_atom("_NET_WM_PID");
			atoms.NET_WM_NAME = get_atom("_NET_WM_NAME");
			atoms.NET_WM_ICON_NAME = get_atom("_NET_WM_ICON_NAME");
			atoms.NET_WM_BYPASS_COMPOSITOR = get_atom("_NET_WM_BYPASS_COMPOSITOR");
			atoms.NET_WM_WINDOW_OPACITY = get_atom("_NET_WM_WINDOW_OPACITY");
			atoms.MOTIF_WM_HINTS = get_atom("_MOTIF_WM_HINTS");

			{
				char name[32];
				snprintf(name, sizeof(name), "_NET_WM_CM_S%u", x11::screen);
				atoms.NET_WM_CM_Sn = get_atom(name);
			}

			// check whether an EWMH-conformant window manager is running
			check_ewmh_support();

			return true;
		}

		bool terminate() {
			if (x11::display == NULL) {
				return false;
			}

			if (x11::display) {
				XCloseDisplay(x11::display);
				x11::display = NULL;
			}

			return true;
		}

		void poll_events() {
			XPending(x11::display);

			while (QLength(x11::display)) {
				XEvent event;
				XNextEvent(x11::display, &event);
				::ct::internal::X11Window::process_event(&event);
				// processEvent(&event);
			}

			XFlush(x11::display);
		}

	} // namespace Platform
} // namespace ct
