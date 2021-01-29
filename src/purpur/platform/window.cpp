
#include <purpur/core/config/platform.hpp>

#include <purpur/platform/window.hpp>

#ifdef PPR_OS_WIN32
	#include <purpur/platform/win32/win32_window.hpp>
    typedef ppr::internal::Win32Window PlatformWindowType;
#elif PPR_OS_MACOS
    #include <purpur/platform/osx/cocoa_window.hpp>
    typedef ppr::internal::CocoaWindow PlatformWindowType;
#endif


#include <iostream>

namespace ppr {

	PlatformWindowType * createWindow(uint32 width, uint32 height, cstr title, uint32 style) {
		return new PlatformWindowType(width, height, title, style);
	}


	Window::Window(internal::NativeWindow * nativeWindow)
	:
	nativeWindow(nativeWindow)
	{}

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

}
