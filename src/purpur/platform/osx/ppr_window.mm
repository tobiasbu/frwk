
#import <purpur/platform/osx/ppr_window.h>

@implementation PPRWindow

	- (BOOL)canBecomeKeyWindow {
		// Required for NSWindowStyleMaskBorderless windows
		return YES;
	}

	- (BOOL)canBecomeMainWindow {
		return YES;
	}

@end
