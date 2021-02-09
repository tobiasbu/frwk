
#include <iostream>
#include <purpur/platform/native_window_type.hpp>
#include <purpur/platform/window.hpp>

namespace ppr {

	NativeWindowType * createWindow(uint32 width, uint32 height, cstr title, uint32 style) {
		return new NativeWindowType(width, height, title, style);
	}

	Window::Window(NativeWindow * nativeWindow) : nativeWindow(nativeWindow) {}

	Window::Window(uint32 width, uint32 height, cstr title, uint32 style) {
		nativeWindow = createWindow(width, height, title, style);
	}

	Window::~Window() {
		if (nativeWindow) {
			delete nativeWindow;
			nativeWindow = NULLPTR;
		}
	}

	bool Window::isVisible() {
		return nativeWindow && nativeWindow->isVisible();
	}

	WindowHandle Window::getHandle() {
		return nativeWindow ? nativeWindow->getHandle() : NULLPTR;
	}

	void Window::setVisible(bool visible) {
		if (nativeWindow) {
			nativeWindow->setVisible(visible);
		}
	}

	void Window::process() {
		if (nativeWindow) {
			nativeWindow->pool();
		}
	}

} // namespace ppr
