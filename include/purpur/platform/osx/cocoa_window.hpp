
#ifndef _PURPURINA_FRWK_COCOA_WINDOW_HPP_
#define _PURPURINA_FRWK_COCOA_WINDOW_HPP_

#include <purpur/core/types.hpp>
#include <purpur/platform/native_window.hpp>

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
		class CocoaWindow : public NativeWindow {

		private:

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
		};

	}

}

#endif
