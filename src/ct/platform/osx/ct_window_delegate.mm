
#import <ct/platform/osx/cocoa_window.hpp>
#import <ct/platform/osx/ct_window_delegate.h>

@implementation CTWindowDelegate

- (instancetype)initWith:(ct::internal::CocoaWindow *)window {
	self = [super init];
    if (self != nil) {
		 cppWindow = window;
	}
	return self;
}

- (BOOL)windowShouldClose:(id)sender
{
    return YES;
}


@end
