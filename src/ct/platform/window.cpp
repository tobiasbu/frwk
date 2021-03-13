

#include <ct/config/os.hpp>
#include <ct/core/assert/assert.hpp>
#include <ct/core/utils/type_traits.hpp>

#include <ct/platform/window.hpp>

#if defined(CT_OS_WIN32)

	#include <ct/platform/win32/win32_window.hpp>
	typedef ct::internal::Win32Window WindowImplType;

#elif defined(CT_OS_MACOS)

	#include <ct/platform/osx/cocoa_window.hpp>
	typedef ct::internal::CocoaWindow WindowImplType;

#else

	#error "Platform not supported"

#endif

namespace ct {

	Window::Window(internal::WindowImpl * _impl) {
		CT_ASSERT(_impl != NULLPTR, "ct::Window: impl is nullptr.");
		this->impl = _impl;
	}

	Window::Window(Window && other) {
		CT_ASSERT(other.impl != NULLPTR, "ct::Window: other.impl is nullptr.");
		impl = MOV(other.impl);
	}

	Window::~Window() {
		close();
	}

	WindowHandle Window::get_handle() const {
		return impl ? impl->get_handle() : NULLPTR;
	}

	vec2i Window::get_position() const {
		return impl ? impl->get_position() : vec2i(-1, -1);
	}

	bool Window::is_visible() const {
		return impl && impl->is_visible();
	}

	void  Window::set_position(const vec2i & position) {
		if (impl) {
			impl->set_position(position);
		}
	}

	void  Window::set_position(const i32 & x, const i32 & y) {
		if (impl) {
			impl->set_position(x, y);
		}
	}

	void Window::set_visible(bool visible) {
		if (impl) {
			impl->set_visible(visible);
		}
	}

	void Window::close() {
		if (impl) {
			delete impl;
			impl = NULLPTR;
		}
	}

	internal::WindowImpl * Window::create_window_impl(const WindowProperties & properties) {
		auto window_impl = WindowImplType::create(properties);
		return window_impl;
	}

	WindowPtr create_window(u32 width, u32 height, cstr title, u32 style) {
		WindowProperties props(width, height, title, style);

		return create_window(props);
	}

	WindowPtr create_window(const WindowProperties & props) {
		auto impl = Window::create_window_impl(props);
		return std::make_unique<enable_make<Window>>(impl);
	}

} // namespace ct
