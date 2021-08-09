

#include <ct/config/os.hpp>
#include <ct/core/assert/assert.hpp>
#include <ct/core/types/type_traits.hpp>

#include <ct/platform/window.hpp>

#if defined(CT_OS_WIN32)

	#include <ct/platform/win32/win32_window.hpp>
typedef ct::internal::Win32Window WindowImplType;

#elif defined(CT_OS_MACOS)

	#include <ct/platform/osx/cocoa_window.hpp>
typedef ct::internal::CocoaWindow WindowImplType;

#elif defined(CT_OS_LINUX)

	#include <ct/platform/x11/x11_window.hpp>
typedef ct::internal::X11Window WindowImplType;

#else
	#error "Platform not supported"
#endif

namespace ct {

	Window::Window() : impl(CT_NULLPTR) {}

	Window::Window(internal::WindowImpl * _impl) {
		CT_ASSERT(_impl != CT_NULLPTR, "ct::Window: impl is nullptr.");
		this->impl = _impl;
	}

	Window::Window(Window && other) {
		CT_ASSERT(other.impl != CT_NULLPTR, "ct::Window: other.impl is nullptr.");
		this->impl = MOV(other.impl);
	}

	Window::~Window() {
		close();
	}

	WindowHandle Window::get_handle() const {
		return impl ? impl->get_handle() : (WindowHandle)0;
	}

	recti Window::get_content_frame() const {
		return impl ? impl->get_content_frame() : recti();
	}

	recti Window::get_frame() const {
		return impl ? impl->get_frame() : recti();
	}

	vec2i Window::get_position() const {
		return impl ? impl->get_position() : vec2i();
	}

	vec2u Window::get_size() const {
		return impl ? impl->get_size() : vec2u();
	}

	bool Window::is_visible() const {
		return impl && impl->is_visible();
	}

	bool Window::is_open() const {
		return impl != CT_NULLPTR;
	}

	cstr Window::get_title() const {
		if (impl) {
			return impl->get_title();
		}
		return CT_NULLPTR;
	}

	void Window::set_frame(const recti & frame) {
		if (impl) {
			impl->set_frame(frame);
		}
	}

	void Window::set_position(const vec2i & position) {
		if (impl) {
			impl->set_position(position);
		}
	}

	void Window::set_position(const i32 & x, const i32 & y) {
		if (impl) {
			impl->set_position(vec2(x, y));
		}
	}

	void Window::set_size(const vec2u & size) {
		if (impl) {
			impl->set_size(size);
		}
	}

	void Window::set_visible(bool visible) {
		if (impl) {
			impl->set_visible(visible);
		}
	}

	void Window::set_title(cstr title) {
		if (impl) {
			impl->set_title(title);
		}
	}

	void Window::close() {
		if (impl) {
			delete impl;
			impl = CT_NULLPTR;
		}
	}

	internal::WindowImpl * Window::create_window_impl(const WindowProperties & properties) {
		auto window_impl = WindowImplType::create(properties);
		return window_impl;
	}

	void Window::create(u32 width, u32 height, cstr title, u32 style) {
		WindowProperties props(width, height, title, style);

		return create(props);
	}

	void Window::create(const WindowProperties & props) {
		impl = Window::create_window_impl(props);
	}


} // namespace ct
