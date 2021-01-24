
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface PPRApplicationDelegate : NSObject <NSApplicationDelegate>

	- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;

	- (void)applicationDidChangeScreenParameters:(NSNotification *)notification;

@end
