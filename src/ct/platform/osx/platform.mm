
#import <ct/platform/osx/ct_application.h>
#import <ct/platform/osx/ct_application_delegate.h>

#include <ct/platform/platform.hpp>

namespace ct {

	namespace Platform {

		namespace detail {

			bool initialized = false;

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
		bool terminate() {
			if (!detail::initialized) {
				return true;
			}

			detail::initialized = false;

			return true;
		}

	} // namespace Platform
} // namespace ct
