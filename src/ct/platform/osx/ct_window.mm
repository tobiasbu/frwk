
#import <ct/platform/osx/ct_window.h>

@implementation CTWindow

	- (BOOL)canBecomeKeyWindow {
		// Required for NSWindowStyleMaskBorderless windows
		return YES;
	}

	- (BOOL)canBecomeMainWindow {
		return YES;
	}

@end
