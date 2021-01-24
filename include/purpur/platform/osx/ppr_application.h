
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface PPRApplication : NSApplication

	-(void)sendEvent:(NSEvent*)anEvent;

	+(void)processEvents;

	+(void)createMenuBar;

@end
