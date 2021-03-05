
#ifndef _CHRONOTRIX_FRWK_COCOA_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_COCOA_WINDOW_HPP_

#include <ct/core/types.hpp>
#include <ct/platform/window_impl.hpp>
#include <ct/platform/window_properties.hpp>

#ifdef __OBJC__
	#import <AppKit/AppKit.h>
	#import <ct/platform/osx/ct_window_delegate.h>
typedef CTWindowDelegate * WindowDelegate;
#else
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
			CocoaWindow(WindowHandle handle, WindowDelegate delegate);

			////////////////////////////////////////////////////////////
			/// \brief Destructor
			///
			////////////////////////////////////////////////////////////
			~CocoaWindow();

			bool is_visible() const;
			WindowHandle get_handle() const;

			void set_visible(bool visible);
			void focus();
			void center();

			static CocoaWindow * create(const WindowProperties & props);
		};

	} // namespace internal

} // namespace ct

#endif
