
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

namespace ppr {
    namespace internal {
        class CocoaWindow;
    }
}

@interface PPRWindowDelegate : NSObject <NSWindowDelegate>
{
	ppr::internal::CocoaWindow* cppWindow;
}

- (instancetype)initWith:(ppr::internal::CocoaWindow *)window;

@end
