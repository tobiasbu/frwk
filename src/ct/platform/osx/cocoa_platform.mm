
#import <ct/platform/osx/ct_application.h>
#import <ct/platform/osx/ct_application_delegate.h>

#include <ct/platform/platform.hpp>

namespace ct {

	namespace Platform {

		namespace detail {

			bool initialized = false;
			CTApplicationDelegate * app_delegate = nil;

			int initApp() {

				static bool appInitialized = false;

				if (appInitialized) {
					return -1;
				}

				[CTApplication sharedApplication];
				[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
				[NSApp activateIgnoringOtherApps:YES];

				// Register an application delegate
				CTApplicationDelegate * appDelegate = [[CTApplicationDelegate alloc] init];

				// TODO: handler appDelegate  error properly
				if (appDelegate == nil) {
					printf("ct::OSX::platformInit: Failed to create application delegate");
					return -1;
				}

				if (![[CTApplication sharedApplication] delegate]) {
					[[CTApplication sharedApplication] setDelegate:appDelegate];
				}

				detail::app_delegate = appDelegate;

				[[CTApplication sharedApplication] finishLaunching];

				[CTApplication createMenuBar];

				appInitialized = true;

				return 0;
			}

		}

		////////////////////////////////////////////////////////////
		bool init() {
			if (detail::initialized) {
				return true;
			}

			if (detail::initApp()) {
				return false;
			}

			return (detail::initialized = true);
		}

		////////////////////////////////////////////////////////////
		void poll_events() {
			@autoreleasepool {
				[CTApplication processEvents];
			}
		}

		////////////////////////////////////////////////////////////
		bool terminate() {
			if (!detail::initialized) {
				return true;
			}

			@autoreleasepool {
				if (detail::app_delegate) {
					[NSApp setDelegate:nil];
					[detail::app_delegate release];
					detail::app_delegate = nil;
				}
			}

			detail::initialized = false;

			return true;
		}

	} // namespace Platform
} // namespace ct
