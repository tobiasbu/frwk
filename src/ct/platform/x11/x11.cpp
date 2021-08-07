
#include <fcntl.h>
#include <libgen.h>
#include <map>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <ct/platform/window_style.hpp>
#include <ct/platform/x11/x11.hpp>

#define MWM_HINTS_FUNCTIONS 1 << 0
#define MWM_HINTS_DECORATIONS 1 << 1

// static const unsigned long MWM_DECOR_ALL         = 1 << 0;
#define MWM_DECOR_BORDER 1 << 1
#define MWM_DECOR_RESIZEH 1 << 2
#define MWM_DECOR_TITLE 1 << 3
#define MWM_DECOR_MENU 1 << 4
#define MWM_DECOR_MINIMIZE 1 << 5
#define MWM_DECOR_MAXIMIZE 1 << 6

// static const unsigned long MWM_FUNC_ALL          = 1 << 0;
#define MWM_FUNC_RESIZE 1 << 1
#define MWM_FUNC_MOVE 1 << 2
#define MWM_FUNC_MINIMIZE 1 << 3
#define MWM_FUNC_MAXIMIZE 1 << 4
#define MWM_FUNC_CLOSE 1 << 5

namespace ct {

	struct WMHints {
		unsigned long flags;
		unsigned long functions;
		unsigned long decorations;
		long inputMode;
		unsigned long state;
	};

	namespace x11 {

		Display * display = NULL;
		u32 screen = -1;
		XID root = 0;
		XContext context = 0;
		i32 last_error_code = Success;
		Atoms atoms = {0};

		int x11_error_handler(Display * errorDisplay, XErrorEvent * event) {
			if (display != errorDisplay) {
				return 0;
			}
			last_error_code = event->error_code;
			return 0;
		}

		i32 get_window_property(Window window, Atom property, Atom type, u8 ** value) {
			Atom actualType;
			i32 actualFormat;
			unsigned long numBytes;
			unsigned long itemCount = 0;

			i32 result = XGetWindowProperty(display,
			                                window,
			                                property,
			                                0,
			                                __LONG_MAX__,
			                                False,
			                                type,
			                                &actualType,
			                                &actualFormat,
			                                &itemCount,
			                                &numBytes,
			                                value);

			if (result != Success || actualType != type || itemCount == 0) {
				return 0;
			}

			return itemCount;
		}

		void catch_error_handler() {
			last_error_code = Success;
			XSetErrorHandler(x11_error_handler);
		}

		void release_error_handler() {
			XSync(display, False);
			XSetErrorHandler(NULL);
		}

		cstr find_executable_name() {
			i32 file = open("/proc/self/cmdline", O_RDONLY | O_NONBLOCK);

			if (!file) {
				return "ct";
			}

			i32 result;
			u32 buffer_size = 256;
			u32 offset = 0;
			char * buffer = (char *)malloc(sizeof(char) * buffer_size);

			while ((result = read(file, &buffer[offset], buffer_size)) > 0) {
				offset += result;
				if (offset > buffer_size) {
					buffer = (char *)realloc(buffer, buffer_size + result * sizeof(*buffer));
					buffer_size += buffer_size;
				}
			}

			close(file);

			if (offset) {
				buffer[offset] = 0;
				return basename(&buffer[0]);
			}

			return "ct";
		}

		WMHints parse_window_style(const WindowProperties & props) {
			WMHints hints;
			hints.inputMode = 0;
			hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
			hints.decorations = 0;
			hints.functions = 0;

			bool titleable = props.has_title();

			if (titleable) {
				hints.decorations |=
				    MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MINIMIZE | MWM_DECOR_MENU;
				hints.functions |= MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE;
			}

			if (props.is_resizable()) {
				hints.decorations |= MWM_DECOR_MAXIMIZE | MWM_DECOR_RESIZEH;
				hints.functions |= MWM_FUNC_MAXIMIZE | MWM_FUNC_RESIZE;
			}

			if (props.is_closable()) {
				hints.decorations |= titleable ? 0 : (MWM_DECOR_BORDER | MWM_DECOR_MENU);
				hints.functions |= MWM_FUNC_CLOSE;
			}
			return hints;
		}

		bool create_window(const WindowProperties & props, Visual* visual, i32 depth, Window & result) {
			bool isFullscreen = false;
			i32 x, y;

			if (!isFullscreen) {
				x = DisplayWidth(x11::display, x11::screen) - props.width / 2;
				y = DisplayHeight(x11::display, x11::screen) - props.height / 2;
			}

			if (visual == NULL) { 
				visual = DefaultVisual(x11::display, x11::screen);
				depth = DefaultDepth(x11::display, x11::screen);
			}

			Colormap xcolormap = DefaultColormap(x11::display, x11::screen);

			const unsigned long xeventmask =
			    ExposureMask | FocusChangeMask | ButtonPressMask | ButtonReleaseMask |
			    ButtonMotionMask | PointerMotionMask | KeyPressMask | KeyReleaseMask |
			    StructureNotifyMask | EnterWindowMask | LeaveWindowMask | VisibilityChangeMask |
			    PropertyChangeMask;

			XSetWindowAttributes xattributes = {0};
			xattributes.colormap = xcolormap;
			xattributes.background_pixel = BlackPixel(x11::display, x11::screen);

			// XCreateColormap(x11::display, x11::root, visual, AllocNone);
			xattributes.override_redirect = False;
			xattributes.event_mask = xeventmask;

			catch_error_handler();

			Window handle = XCreateWindow(x11::display,
			                              x11::root,
			                              x,
			                              y,
			                              props.width,
			                              props.height,
			                              0,
			                              depth,
			                              InputOutput,
			                              visual,
			                              CWBackPixel | CWEventMask,
			                              &xattributes);

			release_error_handler();

			if (!handle) {
				return false;
			}

			// Declare window PID
			if (x11::atoms.NET_WM_PID) {
				const long pid = getpid();

				XChangeProperty(x11::display,
				                handle,
				                x11::atoms.NET_WM_PID,
				                XA_CARDINAL,
				                32,
				                PropModeReplace,
				                reinterpret_cast<const unsigned char *>(&pid),
				                1);
			}

			// Declare protocols
			if (x11::atoms.NET_WM_PING && x11::atoms.WM_PROTOCOLS) {
				Atom protocols[] = {x11::atoms.WM_DELETE_WINDOW, x11::atoms.NET_WM_PING};
				XSetWMProtocols(x11::display, handle, protocols, sizeof(protocols) / sizeof(Atom));
			}

			// Set window type
			if (x11::atoms.NET_WM_WINDOW_TYPE && x11::atoms.NET_WM_WINDOW_TYPE_NORMAL) {
				XChangeProperty(x11::display,
				                handle,
				                x11::atoms.NET_WM_WINDOW_TYPE,
				                XA_ATOM,
				                32,
				                PropModeReplace,
				                (u8 *)&x11::atoms.NET_WM_WINDOW_TYPE_NORMAL,
				                1);
			}

			// Set the  Inter-Client Communication Conventions (ICCCM) initial state to
			// the normal state
			{
				XWMHints * hints = XAllocWMHints();

				if (!hints) {
					return false;
				}
				hints->flags = StateHint;
				hints->initial_state = NormalState;
				XSetWMHints(x11::display, handle, hints);
				XFree(hints);
			}

			// Set window style
			if (!isFullscreen && x11::atoms.MOTIF_WM_HINTS) {
				WMHints hints = parse_window_style(props);

				XChangeProperty(x11::display,
				                handle,
				                x11::atoms.MOTIF_WM_HINTS,
				                x11::atoms.MOTIF_WM_HINTS,
				                32,
				                PropModeReplace,
				                reinterpret_cast<const u8 *>(&hints),
				                5);
			}

			// Set window resizeble hints
			// Hack to force windows managers to disable resize
			if (!props.is_resizable()) {
				XSizeHints * sizeHints = XAllocSizeHints();
				sizeHints->flags = PMinSize | PMaxSize | USPosition;
				sizeHints->min_width = sizeHints->max_width = props.width;
				sizeHints->min_height = sizeHints->max_height = props.height;
				sizeHints->x = x;
				sizeHints->y = y;
				XSetWMNormalHints(x11::display, handle, sizeHints);
				XFree(sizeHints);
			}

			// Set window WM_CLASS
			{
				XClassHint * hint = XAllocClassHint();
				char * name = (char *)find_executable_name();
				hint->res_class = name;
				hint->res_name = name;
				XSetClassHint(x11::display, handle, hint);
				XFree(hint);
			}

			// XSetWindowBackgroundPixmap(x11::display, handle, None);

			// XMapWindow(x11::display, handle);

			// X11Window * window = new X11Window(handle);
			// window->set_title(props.title);
			// window->size = {props.width, props.height};

			// XSaveContext(x11::display, handle, x11::context, (XPointer)window);

			XFlush(x11::display);

			result = handle;
			return true;
		}

		void update_window_normal_hints(const Window & handle, const vec2u & size) {
			XSizeHints* hints = XAllocSizeHints();
			hints->flags = PMinSize | PMaxSize;
			hints->min_width = hints->max_width = size.x;
			hints->min_height = hints->max_height = size.y;
			XSetWMNormalHints(x11::display, handle, hints);
			XFree(hints);		
		}

		void save_window_context(const Window & handle, XPointer window_ptr) {
			XSaveContext(display, handle, context, window_ptr);
		}

	} // namespace x11
} // namespace ct
