
#import <purpur/platform/osx/cocoa_window.hpp>
#import <purpur/platform/osx/ppr_window_delegate.h>

@implementation PPRWindowDelegate

- (instancetype)initWith:(ppr::internal::CocoaWindow *)window {
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
