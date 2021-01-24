
#ifndef _PURPURINA_COCOA_WINDOW_HPP_
#define _PURPURINA_COCOA_WINDOW_HPP_

#include <purpur/core/config.hpp>
#include <purpur/platform/platform_window.hpp>

#ifdef __OBJC__
	#import <AppKit/AppKit.h>
	#import <purpur/platform/osx/ppr_window_delegate.h>
	typedef NSWindow* WindowHandle;
	typedef PPRWindowDelegate* WindowDelegate;
#else
	typedef void * WindowHandle;
	typedef void * WindowDelegate;
#endif

namespace ppr {
	namespace internal {
		class CocoaWindow : public PlatformWindow {

			WindowHandle handle;
			WindowDelegate delegate;

		public:
			////////////////////////////////////////////////////////////
			/// \brief Constructs window instance
			///
			////////////////////////////////////////////////////////////
			CocoaWindow(uint32 width, uint32 height, cstr title, uint32 style);

			////////////////////////////////////////////////////////////
			/// \brief Destructor
			///
			////////////////////////////////////////////////////////////
			~CocoaWindow();

			bool isVisible();
			void setVisible(bool visible);
			void focus();


			void pool();
			CocoaWindow * create(uint32 width, uint32 height, cstr title, uint32 style) const;
		};

	}

}

#endif
