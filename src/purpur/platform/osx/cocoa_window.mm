
#include <purpur/platform/window_style.hpp>

#import <purpur/platform/osx/autorelease_pool.h>
#import <purpur/platform/osx/ppr_application.h>
#import <purpur/platform/osx/ppr_application_delegate.h>
#import <purpur/platform/osx/ppr_window.h>
#import <purpur/platform/osx/ppr_window_delegate.h>

#include <purpur/platform/osx/cocoa_window.hpp>


#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_12
	#define NSWindowStyleMaskTitled NSTitledWindowMask;
#endif

/// From: https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/CocoaDrawingGuide/AdvancedDrawing/AdvancedDrawing.html
@interface GradientView : NSView
@end

@implementation GradientView

////////////////////////////////////////////////////////////
-(void)drawRect:(NSRect)dirtyRect
{
	NSRect        bounds = [self bounds];

    NSBezierPath*    clipShape = [NSBezierPath bezierPath];
    [clipShape appendBezierPathWithRoundedRect:bounds xRadius:40 yRadius:30];


    NSGradient* aGradient = [[[NSGradient alloc]
                    initWithColorsAndLocations:[NSColor redColor], (CGFloat)0.0,
                                            [NSColor orangeColor], (CGFloat)0.166,
                                            [NSColor yellowColor], (CGFloat)0.33,
                                            [NSColor greenColor], (CGFloat)0.5,
                                            [NSColor blueColor], (CGFloat)0.75,
                                            [NSColor purpleColor], (CGFloat)1.0,
                                            nil] autorelease];

    [aGradient drawInBezierPath:clipShape angle:0.0];
}

@end

namespace ppr {

	namespace internal {

		NSUInteger parsePurpurStyleMask(uint32 style) {
			NSUInteger styleMask = NSWindowStyleMaskBorderless;

			if (style & WindowStyle::Title) {
				styleMask |= NSWindowStyleMaskTitled;
			}

			if (style & WindowStyle::Close) {
				styleMask |= NSWindowStyleMaskClosable;
			}

			if (style & WindowStyle::Resize) {
				styleMask |= NSWindowStyleMaskResizable;
			}

			if (style & WindowStyle::Miniaturizable) {
				styleMask |= NSWindowStyleMaskMiniaturizable;
			}

			return styleMask;
		}

		int platformInit() {
			static bool isPlatformInited = false;

			if (isPlatformInited) {
				return 0;
			}

			[PPRApplication sharedApplication];
			[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        	[NSApp activateIgnoringOtherApps:YES];

			// Register an application delegate
			PPRApplicationDelegate * appDelegate = [[PPRApplicationDelegate alloc] init];

			// TODO: handler appDelegate  error properly
			if (appDelegate == nil) {
				printf("purpur::OSX::platformInit: Failed to create application delegate");
				return -1;
			}

        	if (![[PPRApplication sharedApplication] delegate]) {
            	[[PPRApplication sharedApplication] setDelegate:appDelegate];
			}

			[[PPRApplication sharedApplication] finishLaunching];

			[PPRApplication createMenuBar];

			isPlatformInited = true;
			printf("isPlatformInited");
			return 0;
		}

		CocoaWindow::CocoaWindow(uint32 width, uint32 height, cstr title, uint32 style) {

			@autoreleasepool {
				platformInit();

				checkAutoreleasePool();

				PPRWindowDelegate * windowDelegate = [[PPRWindowDelegate alloc] initWith:this];
				// TODO: handle windowDelegate error properly
				if (windowDelegate == nil) {
					printf("Failed to create PPRWindowDelegate");
				}

				NSRect contentRect = NSMakeRect(0, 0, width, height);

				NSUInteger styleMask = parsePurpurStyleMask(style);

				PPRWindow * window = [[PPRWindow alloc]
													initWithContentRect:contentRect
													styleMask:styleMask
													backing:NSBackingStoreBuffered
													defer:NO];
				// TODO: handle window error properly
				if (window == nil) {
					printf("[purpur] ERROR: Failed to create PPRWindow at platform::CocoaWindow.");
				}

				GradientView * myView = [[[GradientView alloc] initWithFrame:contentRect] autorelease];
				if (myView == nil) {
					printf("[purpur] ERROR: Failed to create PPRWindow at platform::CocoaWindow.");
				}
				[window setContentView:myView];

				// set window config
				[window setOpaque:YES];
				[window setHidesOnDeactivate:YES];
				[window setReleasedWhenClosed:NO];
				[window setTitle:[NSString stringWithUTF8String:title]];
				[window center];

				// set window level
				[window setLevel:NSMainMenuWindowLevel+1];

				// set event listeners
				[window setDelegate:windowDelegate];
				[window setAcceptsMouseMovedEvents:YES];
   				[window setIgnoresMouseEvents:NO];

				this->handle = window;
				this->delegate =  windowDelegate;
			}

		}


		CocoaWindow::~CocoaWindow() {
			// TODO: clean-up
    		// [this->delegate release];
			// [this->handle close];
		}

		bool CocoaWindow::isVisible() {
			@autoreleasepool {
				// TODO: recreate this function has `isOpened`
				// In macOS, is visible means "is this window visible in screen"
				// If user minimizes the window it will consider not visible

    			return [handle isVisible];


    		}
		}

		void CocoaWindow::setVisible(bool visible) {
			@autoreleasepool {
				if (visible) {
					[handle orderFront:nil];
				} else {
					[handle orderOut:nil];
				}
			}
		}

		void CocoaWindow::focus() {
			 @autoreleasepool {
				// Make us the active application
				// HACK: This is here to prevent applications using only hidden windows from
				//       being activated, but should probably not be done every time any
				//       window is shown
				[NSApp activateIgnoringOtherApps:YES];
				[handle makeKeyAndOrderFront:nil];
			}
		}

		CocoaWindow * CocoaWindow::create(uint32 width, uint32 height, cstr title, uint32 style) const {
			return new CocoaWindow(width, height, title, style);
		}

		void CocoaWindow::pool() {
			/// TODO: improve event pool
			[PPRApplication processEvents];
			// @autoreleasepool {

			// 	for (;;)
			// 	{
			// 		NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
			// 											untilDate:[NSDate distantPast]
			// 											inMode:NSDefaultRunLoopMode
			// 											dequeue:YES];
			// 		if (event == nil)
			// 			break;

			// 		[NSApp sendEvent:event];
			// 	}

			// } // autoreleasepool
		}
	}

}
