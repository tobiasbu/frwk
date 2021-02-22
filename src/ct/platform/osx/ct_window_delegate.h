
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

namespace ct {
    namespace internal {
        class CocoaWindow;
    }
}

@interface CTWindowDelegate : NSObject <NSWindowDelegate>
{
	ct::internal::CocoaWindow* cppWindow;
}

-(void)setup:(ct::internal::CocoaWindow *)window;

-(BOOL)windowShouldClose:(id)sender;

@end
