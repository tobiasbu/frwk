
#import <ct/platform/osx/ct_window_delegate.h>
#import <ct/platform/osx/cocoa_window.hpp>

@implementation CTWindowDelegate

-(void)setup:(ct::internal::CocoaWindow *)window {
    if (self != nil) {
		 cppWindow = window;
	}
}

-(BOOL)windowShouldClose:(id)sender
{
    return YES;
}


@end
