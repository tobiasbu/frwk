
#import <ct/render/opengl/ct_opengl_view.h>

@implementation CTOpenGLView

- (id)initWithFrame:(NSRect)frameRect {
  return [self initWithFrame:frameRect fullscreen:NO];
}

-(id)initWithFrame:(NSRect)frameRect fullscreen:(BOOL)isFullscreen {
	if ((self = [super initWithFrame:frameRect])) {
		[self setWantsBestResolutionOpenGLSurface:YES];
	}
	return self;
}

- (void)dealloc {
	[super dealloc];
}

- (void)update {
  if ([_openGLContext view] == self) {
    [_openGLContext update];
  }
}

- (void) _surfaceNeedsUpdate:(NSNotification*)notification {
  [self update];
}

@end
