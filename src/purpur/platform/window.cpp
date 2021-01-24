
#include <purpur/core/config.hpp>

#include <purpur/platform/platform_window.hpp>
#include <purpur/platform/window.hpp>

#ifdef PPR_OS_MACOS
    #include <purpur/platform/osx/cocoa_window.hpp>
    typedef ppr::internal::CocoaWindow PlatformWindowType;
#endif

#include <iostream>

namespace ppr {

	PlatformWindowType * createWindow(uint32 width, uint32 height, const char * title) {
		return new PlatformWindowType(width, height, title);
	}


	Window::Window(uint32 width, uint32 height, const char * title) {
		platformWindow = createWindow(width, height, title);
	}

	Window::~Window() {
		if (platformWindow != nullptr) {
			delete platformWindow;
		}
	}

	bool Window::isVisible() {
		return platformWindow != nullptr && platformWindow->isVisible();
	}

	void Window::setVisible(bool visible) {
		if (platformWindow != nullptr) {
			platformWindow->setVisible(visible);
		}
	}

	void Window::process() {
		if (platformWindow) {
			platformWindow->pool();
		}
	}

}
