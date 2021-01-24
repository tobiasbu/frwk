
#import <purpur/platform/osx/ppr_application_delegate.h>

@implementation PPRApplicationDelegate

	- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender {
		return NSTerminateCancel;
	}

	- (void)applicationDidChangeScreenParameters:(NSNotification *)notification {

	}

@end
