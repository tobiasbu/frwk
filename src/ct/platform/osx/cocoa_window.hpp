
#ifndef _CHRONOTRIX_FRWK_COCOA_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_COCOA_WINDOW_HPP_

#include <ct/core/types.hpp>
#include <ct/platform/window_impl.hpp>

#ifdef __OBJC__
	#import <AppKit/AppKit.h>
	#import <ct/platform/osx/ct_window_delegate.h>
typedef NSWindow * WindowHandle;
typedef CTWindowDelegate * WindowDelegate;
#else
typedef void * WindowHandle;
typedef void * WindowDelegate;
#endif

namespace ct {
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

} // namespace ct

#endif
