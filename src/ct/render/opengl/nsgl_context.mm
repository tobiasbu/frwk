
#include <dlfcn.h>
#import <Cocoa/Cocoa.h>

#import <ct/render/opengl/ct_opengl_view.h>

#include <iostream>

#include <ct/platform/window.hpp>
#include <ct/render/opengl/nsgl_context.hpp>

namespace ct {

	namespace internal {

		static CFBundleRef framework = nil;

		bool initNsGl() {
			if (framework != nil) {
				return true;
			}

			// TODO move this to render module initialization
			framework = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));

			if (framework == nil) {
				// "NSGL: Failed to locate OpenGL framework"
				std::cout << "Failed to locate OpenGL framework" << std::endl;
				return false;
			}

			return true;
		}


		NsGlContext::NsGlContext(NSOpenGLContextPtr context, Window * owner)
		:
		context(context),
		owner(owner)
		{}

		NsGlContext::~NsGlContext() {

			@autoreleasepool {

				[context release];
				context = nil;

			}

		}

		void NsGlContext::make_current() {

			@autoreleasepool {

				if (owner) {
					[context makeCurrentContext];
					// if (context != [NSOpenGLContext currentContext]) {
				} else {
					[NSOpenGLContext clearCurrentContext];
				}

			}

		}

		void NsGlContext::swap_buffers() {
			@autoreleasepool {

				if (context) {
					[context flushBuffer];
				}

			}
		}

		glGetProcAddressCb NsGlContext::get_proc_address(cstr procname) {

			CFStringRef symbolName = CFStringCreateWithCString(kCFAllocatorDefault, procname, kCFStringEncodingASCII);
			glGetProcAddressCb symbol = (glGetProcAddressCb)CFBundleGetFunctionPointerForName(framework, symbolName);

			CFRelease(symbolName);

			// static void* image = NULL;

			// if (!image)
			// 	image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

			// return (image ? reinterpret_cast<glGetProcAddressCb>(reinterpret_cast<intptr_t>(dlsym(image, procname))) : 0);

			return symbol;
		}

		NsGlContext * NsGlContext::create(Window* window, const ContextConfig & config) {

			// About Cocoa render contexts
			//   https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html
			//   https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_contexts/opengl_contexts.html#/apple_ref/doc/uid/TP40001987-CH216-SW13

			// Pixel format:
			//   https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_pixelformats/opengl_pixelformats.html

			if (!initNsGl()) {
				return nullptr;
			}

			NSOpenGLPixelFormatAttribute attributes[32];
			int index = 0;
			attributes[index++] = NSOpenGLPFAAccelerated;
			attributes[index++] = NSOpenGLPFAClosestPolicy;

			attributes[index++] = NSOpenGLPFAColorSize;
			attributes[index++] = 24;

			attributes[index++] = NSOpenGLPFADoubleBuffer;

			// 3.2
			attributes[index++] = NSOpenGLPFAOpenGLProfile;
      		attributes[index++] = NSOpenGLProfileVersion3_2Core;
			// legacy 2.1
			// attributes[index++] = NSOpenGLPFAOpenGLProfile;
      		// attributes[index++] = NSOpenGLProfileVersionLegacy;

			attributes[index++] = (NSOpenGLPixelFormatAttribute)0;

			NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc]
											   initWithAttributes:attributes];

			if (pixelFormat == nil) {
				std::cout << "Invalid pixel format" << std::endl;
				return nullptr;
			}

			NSOpenGLContext * ogl_context = [[NSOpenGLContext alloc]
										initWithFormat:pixelFormat
                                        shareContext:nil];

			if (ogl_context == nil) {
				std::cout << "Failed to create context" << std::endl;
				return nullptr;
			}

			NSWindow * window_handle = window->get_handle();
			NSRect frame = [[ window_handle contentView ] frame];
			CGSize size = frame.size;
			CTOpenGLView * view = [[CTOpenGLView alloc]
								  initWithFrame:NSMakeRect(0, 0, size.width, size.height)
								  fullscreen:NO];

			if (view == nil) {
				std::cout << "Failed to create view" << std::endl;
				return nullptr;
			}

			[window_handle setContentView:view];
			[view setOpenGLContext:ogl_context];
			[ogl_context setView:view];

			[pixelFormat release];

			return new NsGlContext(ogl_context, window);

		}

	}

}
