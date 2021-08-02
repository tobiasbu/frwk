
#ifndef _CHRONOTRIX_FRWK_WINDOW_HANDLE_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_HANDLE_HPP_

#include <ct/config.hpp>

#ifdef CT_OS_WINDOWS
struct HWND__;
#endif

namespace ct {

#if defined(CT_OS_WINDOWS)

	typedef HWND__ * WindowHandle;
#elif defined(CT_OS_MACOS)

	#ifdef __OBJC__
		#import <AppKit/AppKit.h>
	typedef NSWindow * WindowHandle;
	#else
	typedef void * WindowHandle;
	#endif

#elif defined(CT_OS_LINUX)
	typedef unsigned long WindowHandle;
#else
	typedef void * WindowHandle;
#endif

} // namespace ct

#endif
