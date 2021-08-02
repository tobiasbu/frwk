// NSGL was deprecated in the 10.14 SDK
// Supressing this annoying warning
#define GL_SILENCE_DEPRECATION

#import <Cocoa/Cocoa.h>


@interface CTOpenGLView : NSOpenGLView
{
  @private
  NSOpenGLContext*   _openGLContext;
}

- (id)initWithFrame:(NSRect)frameRect;
- (id)initWithFrame:(NSRect)frameRect fullscreen:(BOOL)isFullscreen;

- (void)update;
@end
