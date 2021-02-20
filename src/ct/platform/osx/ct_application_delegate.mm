
#import <ct/platform/osx/ct_application_delegate.h>

@implementation CTApplicationDelegate

	- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender {
		return NSTerminateCancel;
	}

	- (void)applicationDidChangeScreenParameters:(NSNotification *)notification {

	}

@end
