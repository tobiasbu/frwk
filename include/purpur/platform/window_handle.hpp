
#ifndef _PURPURINA_FRWK_WINDOW_HANDLE_HPP_
#define _PURPURINA_FRWK_WINDOW_HANDLE_HPP_

#include <purpur/core/types.hpp>

#ifdef PPR_OS_WINDOWS
	 struct HWND__;
#endif

namespace ppr {

#if defined(PPR_OS_WINDOWS)

	typedef HWND__ * WindowHandle;

#elif defined(PPR_OS_MACOS)

	#ifdef __OBJC__
		#import <AppKit/AppKit.h>
		#import <purpur/platform/osx/ppr_window_delegate.h>
		typedef NSWindow* WindowHandle;
		typedef PPRWindowDelegate* WindowDelegate;
	#else
		typedef void * WindowHandle;
		typedef void * WindowDelegate;
	#endif

#else
	typedef void* WindowHandle;
#endif

}



#endif
