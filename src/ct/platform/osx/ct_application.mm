
#import <ct/platform/osx/ct_application.h>


#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_12
	typedef NSKeyUp NSEventTypeKeyUp;
	#define NSEventMaskAny NSAnyEventMask;
#endif


@implementation CTApplication

	-(void)sendEvent:(NSEvent *)anEvent {
		// Fullscreen windows have a strange behaviour with key up. To make
		// sure the user gets an event we call (if possible) sfKeyUp on our
		// custom OpenGL view. See -[SFOpenGLView sfKeyUp:] for more details.

		id firstResponder = [[anEvent window] firstResponder];
		if ([anEvent type] != NSEventTypeKeyUp)
//            || (![firstResponder tryToPerform:@selector(sfKeyUp:) with:anEvent]))
		{
			// It's either not a key up event or no responder has a KeyUp
			// message implemented.
			[super sendEvent:anEvent];
		}
	}

	+(void)processEvents {
		[CTApplication sharedApplication];
		NSEvent* event = nil;

		while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
										untilDate:[NSDate distantPast]
											inMode:NSDefaultRunLoopMode
											dequeue:YES])) // Remove the event from the queue
		{
			[NSApp sendEvent:event];
		}
	}

	+(void)createMenuBar
	{
		[CTApplication sharedApplication];

		NSMenu* mainMenu = [NSApp mainMenu];
		if (mainMenu != nil) {
			return;
		}

		mainMenu = [[[NSMenu alloc] initWithTitle:@""] autorelease];
		[NSApp setMainMenu:mainMenu];

	}

@end
