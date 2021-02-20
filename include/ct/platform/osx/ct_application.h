
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface CTApplication : NSApplication

	-(void)sendEvent:(NSEvent*)anEvent;

	+(void)processEvents;

	+(void)createMenuBar;

@end
