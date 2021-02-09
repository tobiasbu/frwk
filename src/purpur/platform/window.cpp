

#include <purpur/core/config/os_detection.hpp>
#include <purpur/core/utils/type_traits.hpp>
#include <purpur/platform/window.hpp>

#if defined(PPR_OS_WIN32)

	#include <purpur/platform/win32/win32_window.hpp>
typedef ppr::internal::Win32Window WindowImplType;

#elif defined(PPR_OS_MACOS)

	#include <purpur/platform/osx/cocoa_window.hpp>
typedef ppr::internal::CocoaWindow WindowImplType;

#else

	#error "Platform not supported"

#endif

namespace ppr {

	Window::Window(WindowImpl * nativeWindow) {
		this->nativeWindow = std::unique_ptr<WindowImpl>(nativeWindow);
	}

	Window::~Window() {
		// if (nativeWindow) {
		// 	delete nativeWindow;
		// 	nativeWindow = NULLPTR;
		// }
	}

	bool Window::isVisible() const {
		return nativeWindow && nativeWindow->isVisible();
	}

	WindowHandle Window::getHandle() const {
		return nativeWindow ? nativeWindow->getHandle() : NULLPTR;
	}

	void Window::setVisible(bool visible) {
		if (nativeWindow) {
			nativeWindow->setVisible(visible);
		}
	}

	std::unique_ptr<Window> Window::create(uint32 width, uint32 height, cstr title, uint32 style) {

		WindowProperties props(
			width,
			height,
			title,
			style
		);

		return Window::create(props);

	}

	std::unique_ptr<Window> Window::create(const WindowProperties & props) {
		auto nativeWindow = WindowImplType::create(props);
		return std::make_unique<enable_make<Window>>(nativeWindow);
	}

} // namespace ppr
