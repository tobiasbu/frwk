
#ifndef _PURPURINA_FRWK_NATIVE_WINDOW_TYPE_HPP_
#define _PURPURINA_FRWK_NATIVE_WINDOW_TYPE_HPP_

#include <purpur/core/config/platform.hpp>

#if defined(PPR_OS_WIN32)

	#include <purpur/platform/win32/win32_window.hpp>
typedef ppr::internal::Win32Window NativeWindowType;

#elif defined(PPR_OS_MACOS)

	#include <purpur/platform/osx/cocoa_window.hpp>
typedef ppr::internal::CocoaWindow NativeWindowType;

#else

	#error "Platform not supported"

#endif

#endif
