
#import <purpur/platform/osx/ppr_application.h>
#import <purpur/platform/osx/ppr_application_delegate.h>

#include <purpur/platform/platform.hpp>

namespace ppr {

	namespace Platform {

		namespace detail {

			bool initialized = false;

			int initApp() {

				static bool appInitialized = false;

				if (appInitialized) {
					return -1;
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
} // namespace ppr
