
#ifndef _PURPURINA_FRWK_COCOA_WINDOW_HPP_
#define _PURPURINA_FRWK_COCOA_WINDOW_HPP_

#include <purpur/core/types.hpp>
#include <purpur/platform/window_impl.hpp>

#ifdef __OBJC__
	#import <AppKit/AppKit.h>
	#import <purpur/platform/osx/ppr_window_delegate.h>
typedef NSWindow * WindowHandle;
typedef PPRWindowDelegate * WindowDelegate;
#else
typedef void * WindowHandle;
typedef void * WindowDelegate;
#endif

namespace ppr {
	namespace internal {
		class CocoaWindow : public WindowImpl {
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

			bool isVisible() const;
			WindowHandle getHandle() const;

			void setVisible(bool visible);
			void focus();
			void center();

			void pool();
		};

	} // namespace internal

} // namespace ppr

#endif
