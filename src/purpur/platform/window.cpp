
#include <purpur/core/config.hpp>

#include <purpur/platform/platform_window.hpp>
#include <purpur/platform/window.hpp>

#ifdef PPR_OS_MACOS
    #include <purpur/platform/osx/cocoa_window.hpp>
    typedef ppr::internal::CocoaWindow PlatformWindowType;
#endif

#include <iostream>

namespace ppr {

	PlatformWindowType * createWindow(uint32 width, uint32 height, cstr title, uint32 style) {
		return new PlatformWindowType(width, height, title, style);
	}


	Window::Window(uint32 width, uint32 height, cstr title, uint32 style) {
		platformWindow = createWindow(width, height, title, style);
	}

	Window::~Window() {
		if (platformWindow) {
			delete platformWindow;
			platformWindow = NULLPTR;
		}
	}

	bool Window::isVisible() {
		return platformWindow && platformWindow->isVisible();
	}

	void Window::setVisible(bool visible) {
		if (platformWindow) {
			platformWindow->setVisible(visible);
		}
	}

	void Window::process() {
		if (platformWindow) {
			platformWindow->pool();
		}
	}

}
