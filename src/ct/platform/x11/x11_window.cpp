
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <ct/config.hpp>
#include <ct/platform/x11/x11.hpp>
#include <ct/platform/x11/x11_window.hpp>

namespace ct {

	namespace internal {

		/// TODO(@tobiasbu) Create timer utility.
		namespace timer {

			bool timer_initted = false;
			bool has_monotonic = false;
			struct timespec start;

			// from https://www.eecis.udel.edu/~mills/leap.html
			// 31 Dec 98 23:59:59 translated to seconds since 1900 minus
			// 31 Dec 98 23:59:59 translated to seconds since 1970 gives
			// the UTC to NTP offset
			constexpr u32 UNIX_NTP_OFFSET = 3124137599 - 915148799;

			void init() {
				if (timer_initted) {
					return;
				}
				timer_initted = true;

				if (clock_gettime(CLOCK_MONOTONIC, &start) == 0) {
					has_monotonic = true;
				}
			}

			// since init
			u32 get_tick() {
				init();

				u32 ticks = 0;
				if (has_monotonic) {
					struct timespec ts;
					clock_gettime(CLOCK_MONOTONIC, &ts);
					ticks = (u32)((ts.tv_sec - start.tv_sec) * 1000 +
					              (ts.tv_nsec - start.tv_nsec) / 1000000);
				}
				return ticks;
			}

			void sleep(u32 milliseconds) {
				struct timeval tv;
				i32 error;
				u32 now, delta = 0;
				u32 last = get_tick();

				while (true) {
					now = get_tick();
					delta = now - last;
					if (delta >= milliseconds) {
						break;
					}
					milliseconds -= delta;
					last = now;

					tv.tv_sec = milliseconds / 1000;
					tv.tv_usec = (milliseconds % 1000) * 1000;
					if (select(0, NULL, NULL, NULL, &tv)) {
						break;
					}
				}
			}

		} // namespace timer

		bool get_frame_extents(Window handle, X11Borders & borders) {
			Atom actual_type;
			i32 actual_format;
			unsigned long nitems, bytes_after;
			u8 * property;
			bool result = false;

			if (XGetWindowProperty(x11::display,
			                       handle,
			                       x11::atoms.NET_FRAME_EXTENTS,
			                       0,
			                       16,
			                       0,
			                       XA_CARDINAL,
			                       &actual_type,
			                       &actual_format,
			                       &nitems,
			                       &bytes_after,
			                       &property) == Success) {
				if (actual_type != None && nitems == 4) {
					long * prop_borders = (long *)property;
					borders.left = (i32)prop_borders[0];
					borders.right = (i32)prop_borders[1];
					borders.top = (i32)prop_borders[2];
					borders.bottom = (i32)prop_borders[3];
					result = true;
				}
			}
			if (property != NULL) {
				XFree(property);
			}
			return result;
		}

		Bool is_MapNotify(Display * dpy, XEvent * ev, XPointer win) {
			return ev->type == MapNotify && ev->xmap.window == *((Window *)win);
		}

		X11Window::X11Window(Window handle) : handle(handle) {}

		X11Window::~X11Window() {
			dispose();
		}

		WindowHandle X11Window::get_handle() const {
			return handle;
		}

		recti X11Window::get_content_frame() const {
			Window child;
			X11Borders borders;
			vec2i pos;

			// Includes decorations!
			XTranslateCoordinates(x11::display,
			                      handle,
			                      DefaultRootWindow(x11::display),
			                      0,
			                      0,
			                      &pos.x,
			                      &pos.y,
			                      &child);

			return recti(pos, get_size());
		}

		recti X11Window::get_frame() const {
			Window child;
			X11Borders borders;
			vec2i pos;
			vec2u size = get_size();

			// Includes decorations!
			XTranslateCoordinates(x11::display,
			                      handle,
			                      DefaultRootWindow(x11::display),
			                      0,
			                      0,
			                      &pos.x,
			                      &pos.y,
			                      &child);

			if (get_frame_extents(handle, borders)) {
				pos.x -= borders.left + borders.right;
				pos.y -= borders.top + borders.bottom;
				size.x += borders.left + borders.right;
				size.y += borders.top + borders.bottom;
			}

			return recti(pos, size);
		}

		vec2i X11Window::get_position() const {
			Window child;
			X11Borders borders;
			vec2i pos;

			// Includes decorations!
			XTranslateCoordinates(x11::display,
			                      handle,
			                      DefaultRootWindow(x11::display),
			                      0,
			                      0,
			                      &pos.x,
			                      &pos.y,
			                      &child);

			

			// Modern WMs supports EWMH with _NET_FRAME_EXTENTS atom which includes window borders size. 
			// If is present, get the borders size and subtract to have the exact position of top-left corners
			if (get_frame_extents(handle, borders)) {
				return {pos.x - borders.left, pos.y - borders.top};
			}

			return {pos.x, pos.y};
		}

		vec2u X11Window::get_size() const {
			XWindowAttributes attribs;
			XGetWindowAttributes(x11::display, handle, &attribs);
			return vec2u(attribs.width, attribs.height);
		}

		cstr X11Window::get_title() const {
			char * window_name;
			if (!XFetchName(x11::display, handle, &window_name)) {
				return "";
			}
			return window_name;
		}

		bool X11Window::is_visible() const {
			if (!handle) {
				return false;
			}

			XWindowAttributes attribs;
			XGetWindowAttributes(x11::display, handle, &attribs);

			return attribs.map_state == IsViewable;
		};

		void X11Window::set_frame(const recti & frame) {
			XWindowAttributes attribs;
			Window parent_window, root, child_return;
			Window * children_windows;
			u32 timeout, children_count;
			vec2i src_pos, src_size, frame_size = frame.size;
			X11Borders borders;

			XSync(x11::display, False);
			XQueryTree(
			    x11::display, handle, &root, &parent_window, &children_windows, &children_count);
			
			XGetWindowAttributes(x11::display, handle, &attribs);
			src_size.x = attribs.width;
			src_size.y = attribs.height;
			if (get_frame_extents(handle, borders)) {
				frame_size.x -= borders.left + borders.right;
				frame_size.y -= borders.top + borders.bottom;
			}

			XTranslateCoordinates(x11::display,
			                      parent_window,
			                      x11::root,
			                      attribs.x,
			                      attribs.y,
			                      &src_pos.x,
			                      &src_pos.y,
			                      &child_return);

			if (!resizable) {
				x11::update_window_normal_hints(handle, frame_size);
			}
			XResizeWindow(x11::display, handle, frame_size.x, frame_size.y);
			XMoveWindow(x11::display, handle, frame.x, frame.y);

			/*
			 * Unfortunately in some WMs changing position does not happen immediately
			 * We'll wait a small time to check if WM change the window position
			 */
			timeout = timer::get_tick() + 100;
			while (true) {
				vec2i new_pos;
				XSync(x11::display, False);
				XGetWindowAttributes(x11::display, handle, &attribs);
				XTranslateCoordinates(x11::display,
				                      parent_window,
				                      x11::root,
				                      attribs.x,
				                      attribs.y,
				                      &new_pos.x,
				                      &new_pos.y,
				                      &child_return);
				if ((new_pos.x != src_pos.x || new_pos.y != src_pos.y) && (attribs.width != src_size.x || attribs.height != src_size.y)) {
					this->size.x = frame.width;
					this->size.y = frame.height;
					break;
				} else if ((new_pos.x == src_pos.x && new_pos.y == src_pos.y) && (attribs.width == frame.width && attribs.height == frame.height)) {
					break;
				}

				if (timer::get_tick() > timeout) {
					break;
				}
				timer::sleep(10);
			}
		}

		void X11Window::set_position(const vec2i & position) {
			XWindowAttributes attribs;
			Window parent_window, root, child_return;
			Window * children_windows;
			u32 timeout, children_count;
			vec2i src;

			XSync(x11::display, False);
			/* queries root ID, window parent, childrens and children count */
			XQueryTree(
			    x11::display, handle, &root, &parent_window, &children_windows, &children_count);
			XGetWindowAttributes(x11::display, handle, &attribs);
			XTranslateCoordinates(x11::display,
			                      parent_window,
			                      x11::root,
			                      attribs.x,
			                      attribs.y,
			                      &src.x,
			                      &src.y,
			                      &child_return);

			XMoveWindow(x11::display, handle, position.x, position.y);;

			/*
			 * Unfortunately in some WMs changing position does not happen immediately
			 * We'll wait a small time to check if WM change the window position
			 */
			timeout = timer::get_tick() + 100;
			while (true) {
				vec2i new_pos;
				XSync(x11::display, False);
				XGetWindowAttributes(x11::display, handle, &attribs);
				XTranslateCoordinates(x11::display,
				                      parent_window,
				                      x11::root,
				                      attribs.x,
				                      attribs.y,
				                      &new_pos.x,
				                      &new_pos.y,
				                      &child_return);
				if ((new_pos.x != src.x) || (new_pos.y != src.y)) {
					break;
				} else if ((new_pos.x == position.x) && (new_pos.y == position.y)) {
					break;
				}

				if (timer::get_tick() > timeout) {
					break;
				}
				timer::sleep(10);
			}
		}

		void X11Window::set_size(const vec2u & size) {
			XWindowAttributes attribs;
			vec2i src_size;
			u32 timeout;

			XSync(x11::display, False);
			XGetWindowAttributes(x11::display, handle, &attribs);
			src_size.x = attribs.width;
			src_size.y = attribs.height;

			if (!resizable) {
				x11::update_window_normal_hints(handle, size);
			}
			XResizeWindow(x11::display, handle, size.x, size.y);

			/*
			 * Unfortunately in some WMs the resize does not happen immediately
			 * We'll wait a small time to check if WM the accepts the resize
			 */
			timeout = timer::get_tick() + 100;
			while (true) {
				XSync(x11::display, False);
				XGetWindowAttributes(x11::display, handle, &attribs);
				if ((attribs.width != src_size.x) || (attribs.height != src_size.y)) {
					this->size.x = size.x;
					this->size.y = size.y;
					break;
				} else if ((attribs.width == size.x) && (attribs.height == size.y)) {
					break;
				}

				if (timer::get_tick() > timeout) {
					break;
				}
				timer::sleep(10);
			}
		
		}

		void X11Window::set_title(cstr title) {
			const x11::Atoms & atoms = x11::atoms;

			// Set NET_WM_NAME title
			XChangeProperty(x11::display,
			                handle,
			                atoms.NET_WM_NAME,
			                atoms.UTF8_STRING,
			                8,
			                PropModeReplace,
			                (u8 *)title,
			                strlen(title));

			// Set NET_WM_ICON_NAME title
			XChangeProperty(x11::display,
			                handle,
			                atoms.NET_WM_ICON_NAME,
			                atoms.UTF8_STRING,
			                8,
			                PropModeReplace,
			                (u8 *)title,
			                strlen(title));

			XFlush(x11::display);

#if defined(X_HAVE_UTF8_STRING)
			Xutf8SetWMProperties(x11::display, handle, title, title, NULL, 0, NULL, NULL, NULL);
#endif
		}

		void X11Window::set_visible(bool visible) {
			bool mapped = is_mapped();
			if (visible && !mapped) {
				XEvent event;

				XMapWindow(x11::display, handle);
				XIfEvent(x11::display, &event, &is_MapNotify, (XPointer)&handle);
				XFlush(x11::display);

			} else if (!visible && mapped) {
				XUnmapWindow(x11::display, handle);
				XFlush(x11::display);
			}
		}

		bool X11Window::is_mapped() const {
			XWindowAttributes windowAttributes;
			XGetWindowAttributes(x11::display, handle, &windowAttributes);

			return windowAttributes.map_state != IsUnmapped;
		}

		void X11Window::dispose() {
			if (handle) {
				XDeleteContext(x11::display, handle, x11::context);
				XUnmapWindow(x11::display, handle);
				XDestroyWindow(x11::display, handle);
				handle = (Window)0;
			}
			if (x11::display) {
				XFlush(x11::display);
			}
		}

		void X11Window::process_event(XEvent * event) {
			Bool filtered = XFilterEvent(event, None);

			X11Window * xwindow = CT_NULLPTR;
			if (XFindContext(
			        x11::display, event->xany.window, x11::context, (XPointer *)&xwindow) != 0) {
				return;
			}

			switch (event->type) {
				default: break;

				case ClientMessage:
					if (filtered) {
						return;
					}

					if (event->xclient.message_type == None) {
						return;
					}

					if (event->xclient.message_type == x11::atoms.WM_PROTOCOLS) {
						const Atom protocol = event->xclient.data.l[0];
						if (protocol == None) {
							return;
						}

						if (protocol == x11::atoms.WM_DELETE_WINDOW) {
							// WM ask to close the window.
							// For example: by the user pressing a 'close' window decoration button
							xwindow->dispose();

						} else if (protocol == x11::atoms.NET_WM_PING) {
							XEvent reply = *event;
							reply.xclient.window = x11::root;

							// WM is pinging the application to ensure it's still responding

							XSendEvent(x11::display,
							           x11::root,
							           False,
							           SubstructureNotifyMask | SubstructureRedirectMask,
							           &reply);
						}
					}

					break;

				case ConfigureNotify:
					//
					if (event->xconfigure.width != xwindow->size.x ||
					    event->xconfigure.height != xwindow->size.y) {
						xwindow->size = {event->xconfigure.width, event->xconfigure.height};
					}
					break;

				case PropertyNotify:
					break;
			}
		}

		X11Window * X11Window::create(const WindowProperties & props) {
			Window result;
			if (x11::create_window(props, NULL, -1, result)) {
				X11Window * window = new X11Window(result);
				window->resizable = props.is_resizable();
				window->size = {props.width, props.height};
				window->set_title(props.title);
				window->set_visible(true);
				x11::save_window_context(result, (XPointer)window);
				return window;
			}

			return CT_NULLPTR;
		}

	} // namespace internal

} // namespace ct
