
#import <ct/platform/osx/ctwindow.h>

@implementation CTWindow

	- (BOOL)canBecomeKeyWindow {
		// Required for NSWindowStyleMaskBorderless windows
		return YES;
	}

	- (BOOL)canBecomeMainWindow {
		return YES;
	}

@end
