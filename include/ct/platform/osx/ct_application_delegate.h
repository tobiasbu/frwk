
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface CTApplicationDelegate : NSObject <NSApplicationDelegate>

	- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;

	- (void)applicationDidChangeScreenParameters:(NSNotification *)notification;

@end
