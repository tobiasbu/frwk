
#ifndef _PURPURINA_WINDOW_HANDLE_HPP_
#define _PURPURINA_WINDOW_HANDLE_HPP_

#include <purpur/core/config.hpp>

#ifdef PPR_OS_WIN32
	struct HWND__;
#endif

namespace ppr {

	#ifdef PPR_OS_WIN32

		typedef HWND__ * WindowHandle;

	#elif PPR_OS_MACOS

		#ifdef __OBJC__
			#import <AppKit/AppKit.h>
			#import <purpur/platform/osx/ppr_window_delegate.h>
			typedef NSWindow* WindowHandle;
			typedef PPRWindowDelegate* WindowDelegate;
		#else
			typedef void * WindowHandle;
			typedef void * WindowDelegate;
		#endif

	#endif

}

#endif
