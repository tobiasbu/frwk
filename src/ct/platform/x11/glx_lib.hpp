
#ifndef _CHRONOTRIX_FRWK_GLX_LIB_HPP_
#define _CHRONOTRIX_FRWK_GLX_LIB_HPP_

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <ct/config.hpp>
#include <ct/core/utils/helper_macros.hpp>

#ifndef Bool
	#define Bool int;
#endif

// Enumerators - Tokens

// See: https://www.sci.utah.edu/~jmk/arbeit_doc/html/glxew_8h.html

#define GLX_RGBA_TYPE 0x8014

#define GLX_RENDER_TYPE 0x8011
#define GLX_RGBA_BIT 0x00000001

#define GLX_DRAWABLE_TYPE 0x8010
#define GLX_WINDOW_BIT 0x00000001
#define GLX_PIXMAP_BIT 0x00000002
#define GLX_PBUFFER_BIT 0x00000004

#define GLX_VENDOR 0x1
#define GLX_DOUBLEBUFFER 5
#define GLX_STEREO 6
#define GLX_AUX_BUFFERS 7
#define GLX_RED_SIZE 8
#define GLX_GREEN_SIZE 9
#define GLX_BLUE_SIZE 10
#define GLX_ALPHA_SIZE 11
#define GLX_DEPTH_SIZE 12
#define GLX_STENCIL_SIZE 13
#define GLX_ACCUM_RED_SIZE 14
#define GLX_ACCUM_GREEN_SIZE 15
#define GLX_ACCUM_BLUE_SIZE 16
#define GLX_ACCUM_ALPHA_SIZE 17
#define GLX_SAMPLES 0x186a1

// See: https://www.khronos.org/registry/OpenGL/extensions/ARB/GLX_ARB_create_context.txt
#define GLX_CONTEXT_DEBUG_BIT_ARB 0x0001
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
#define GLX_CONTEXT_FLAGS_ARB 0x2094
#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
// https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_robustness.txt
#define GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x00000004
#define GLX_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GLX_NO_RESET_NOTIFICATION_ARB 0x8261
#define GLX_LOSE_CONTEXT_ON_RESET_ARB 0x8252
// See: https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_context_flush_control.txt
#define GLX_CONTEXT_RELEASE_BEHAVIOR_ARB 0x2097
#define GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB 0x0000
#define GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB 0x2098
// See: https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_create_context_no_error.txt
#define GLX_CONTEXT_OPENGL_NO_ERROR_ARB 0x31B3

// X11 glX structs
typedef XID X11WindowHandle;
typedef XID GLXWindow;
typedef XID GLXDrawable;
typedef struct __GLXFBConfig * GLXFBConfig;
typedef struct __GLXcontext * GLXContext;

namespace ct {

	/**
	* @brief  'OpenGL Extension to the X Window System' (GLX)
	*/
	namespace glx {

		// Client functions

		using PFN_glXQueryExtension = Bool (*)(Display * dpy, i32 * errorBase, i32 * eventBase);
		using PFN_glXQueryExtensionsString = cstr (*)(Display * dpy, i32 screen);
		using PFN_glXQueryVersion = Bool (*)(Display *, i32 * major, i32 * minor);
		using PFN_glXGetClientString = cstr (*)(Display * dpy, i32 name);
		using PFN_glXGetProcAddress = void * (*)(ucstr procName);

		// On-screen rendering

		using PFN_glXCreateWindow = GLXWindow (*)(Display * dpy,
		                                          GLXFBConfig config,
		                                          X11WindowHandle win,
		                                          const int * attrib_list);
		using PFN_glXDestroyWindow = void (*)(Display * dpy, GLXWindow win);

		// Context functions

		using PFN_glXCreateNewContext = GLXContext (*)(Display * dpy,
		                                               GLXFBConfig config,
		                                               int render_type,
		                                               GLXContext share_list,
		                                               Bool direct);
		using PFN_glXDestroyContext = void (*)(Display * dpy, GLXContext ctx);
		using PFN_glXMakeCurrent = Bool (*)(Display * dpy, GLXDrawable drawable, GLXContext ctx);
		using PFN_glXSwapBuffers = void (*)(Display * dpy, GLXDrawable drawable);

		// Framebuffer functions

		using PFN_glXGetFBConfigAttrib = i32 (*)(Display * dpy,
		                                         GLXFBConfig config,
		                                         i32 attribute,
		                                         i32 * value);
		using PFN_glXGetFBConfigs = GLXFBConfig * (*)(Display * dpy, i32 screen, i32 * nelements);
		using PFN_glXGetVisualFromFBConfig = XVisualInfo * (*)(Display * dpy, GLXFBConfig config);

		// glX extensions functions

		using PFN_glXGetProcAddressARB = void * (*)(ucstr procName);
		using PFN_glXSwapIntervalEXT = void * (*)(Display * dpy,
		                                          GLXDrawable drawable,
		                                          i32 interval);
		using PFN_glXSwapIntervalSGI = i32 (*)(i32 interval);
		using PFN_glXSwapIntervalMESA = i32 (*)(u32 interval);
		using PFN_glXCreateContextAttribsARB = GLXContext (*)(Display * dpy,
		                                                      GLXFBConfig config,
		                                                      GLXContext share_context,
		                                                      Bool direct,
		                                                      i32 * attrib_list);

		/**
		 * @brief Define GLX extensions availability flags
		 */
		struct glXExtensionsFlags {
			bool EXT_visual_info;
			bool EXT_visual_rating;
			bool EXT_import_context;
			bool EXT_swap_control;
			bool EXT_swap_control_tear;
			bool EXT_texture_from_pixmap;
			bool EXT_buffer_age;
			bool EXT_create_context_es_profile;
			bool EXT_create_context_es2_profile;
			bool EXT_stereo_tree;
			bool EXT_framebuffer_sRGB;
			bool SGIX_fbconfig;
			bool SGIX_pbuffer;
			bool SGI_video_sync;
			bool SGI_swap_control;
			bool NV_delay_before_swap;
			bool NV_robustness_video_memory_purge;
			bool NV_float_buffer;
			bool NV_multisample_coverage;
			bool NV_copy_image;
			bool ARB_create_context;
			bool ARB_create_context_profile;
			bool ARB_create_context_no_error;
			bool ARB_create_context_robustness;
			bool ARB_context_flush_control;
			bool ARB_multisample;
			bool ARB_fbconfig_float;
			bool ARB_get_proc_address;
			bool MESA_swap_control;
		};

		/**
		* @brief Define GLX extension function pointers 
		*/
		struct glXExtensions {

			/**
			 * @brief Obtain a pointer to an GLX or OpenGL functions
			 *
			 * @param procName Specifies the name of the OpenGL or GLX function whose address is to be returned.
			 *
			 * @see https://www.ibm.com/docs/en/aix/7.1?topic=environment-glxgetprocaddressarb-subroutine
			 */
			PFN_glXGetProcAddressARB get_proc_address_arb;

			/**
			 * @brief Specifies the minimum number of video frame periods per buffer swap for
			 * a particular GLX drawable
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param drawable GLX drawable
			 * @param interval The swap interval
			 *
			 * @see https://www.khronos.org/registry/OpenGL/extensions/EXT/EXT_swap_control.txt
			 */
			PFN_glXSwapIntervalEXT swap_interval_ext;

			/**
			 * @brief Specifies the minimum number of video frame periods per buffer swap.
			 *
			 * Calling glXSwapIntervalSGI is equivalent to calling glXSwapIntervalEXT on
			 * the current drawable, if one exists.
			 *
			 * @param interval The swap interval
			 *
			 * @see https://nixdoc.net/man-pages/irix/man3/OpenGL/glxswapintervalsgi.3.html
			 */
			PFN_glXSwapIntervalSGI swap_interval_sgi;

			/**
			 * @brief This extension allows an application to specify a minimum periodicity
			 * of color buffer swaps, measured in video frame periods.
			 *
			 * @param interval The swap interval
			 *
			 * @see https://www.khronos.org/registry/OpenGL/extensions/MESA/GLX_MESA_swap_control.txt
			 */
			PFN_glXSwapIntervalMESA swap_interval_mesa;

			/**
			 * @brief Create new OpenGL context by specifying attributes
			 * like the GL version and context properties.
			 *
			 * Additionally must add an attribute specifying the GL profile requested
			 * for a context of OpenGL 3.2 or later.
			 *
			 * @see https://www.khronos.org/registry/OpenGL/extensions/ARB/GLX_ARB_create_context.txt
			 */
			PFN_glXCreateContextAttribsARB create_context_attribs_arb;
		};

		/**
		 * @brief Define main GLX functions pointers
		 *
		 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/
		 */
		struct glXFuncs {
			/**
			 * @brief Return the version numbers of the GLX extension
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param major Returns the major version number of the GLX server extension.
			 * @param minor Returns the minor version number of the GLX server extension.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXQueryVersion.xml
			 */
			PFN_glXQueryVersion query_version;

			/**
			 * @brief Indicate whether the GLX extension is supported
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param errorBase Returns the base error code of the GLX server extension.
			 * @param eventBase Returns the base event code of the GLX server extension.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXQueryExtension.xml
			 */
			PFN_glXQueryExtension query_extension;

			/**
			 * @brief Return list of supported extensions
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param screen Specifies the screen number.
			 *
			 */
			PFN_glXQueryExtensionsString query_extensions_string;

			/**
			 * @brief Return a string describing the client
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param name Specifies which string is returned. The symbolic constants GLX_VENDOR,
			 * GLX_VERSION, and GLX_EXTENSIONS are accepted.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXGetClientString.xml
			 */
			PFN_glXGetClientString get_client_string;

			/**
			 * @brief Obtain a pointer to an OpenGL or GLX function
			 *
			 * @param procName Specifies the name of the OpenGL or GLX function whose address is to be returned.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXGetProcAddress.xml
			 */
			PFN_glXGetProcAddress get_proc_address;

			/**
			 * @brief Create a new GLX rendering context
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param config Specifies the GLXFBConfig structure with the desired attributes for the context.
			 * @param render_type Specifies the type of the context to be created. Must be one of
			 * GLX_RGBA_TYPE or GLX_COLOR_INDEX_TYPE.
			 * @param Specifies the context with which to share display lists. NULL indicates that no
			 * sharing is to take place.
			 * @param Specifies whether rendering is to be done with a direct connection to the graphics
			 * system if possible (True) or through the X server (False).
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXCreateNewContext.xml
			 */
			PFN_glXCreateNewContext create_new_context;

			/**
			 * @brief Destroy a GLX context
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param ctx Specifies the GLX context to be destroyed
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXDestroyContext.xml
			 */
			PFN_glXDestroyContext destroy_context;

			/**
			 * @brief Attach a GLX context to a window or a GLX pixmap
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param drawable Specifies a GLX drawable. Must be either an XWindow ID or a GLX pixmap ID.
			 * @param ctx Specifies a GLX rendering context that is to be attached to drawable.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXMakeCurrent.xml
			 */
			PFN_glXMakeCurrent make_current;

			/**
			 * @brief Exchange front and back buffers
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param drawable Specifies the drawable whose buffers are to be swapped.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXSwapBuffers.xml
			 */
			PFN_glXSwapBuffers swap_buffers;

			/**
			 * @brief Create an on-screen rendering area
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param config Specifies a GLXFBConfig structure with the desired attributes for the window.
			 * @param win Specifies the X window to be used as the rendering area.
			 * @param attrib_list Currently unused. This must be set to NULL or be an empty list
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXCreateWindow.xml
			 */
			PFN_glXCreateWindow create_window;

			/**
			 * @brief Destroy an on-screen rendering area
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param win Specifies the GLXWindow to be destroyed.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXDestroyWindow.xml
			 */
			PFN_glXDestroyWindow destroy_window;

			/**
			 * @brief List all GLX frame buffer configurations for a given screen
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param screen Specifies the screen number.
			 * @param nelements Returns the number of GLXFBConfigs returned.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXGetFBConfigs.xml
			 */
			PFN_glXGetFBConfigs get_fb_configs;

			/**
			 * @brief Return information about a GLX frame buffer configuration
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param config Specifies the GLX frame buffer configuration to be queried.
			 * @param attribute Specifies the attribute to be returned.
			 * @param value Returns the requested value.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXGetFBConfigAttrib.xml
			 */
			PFN_glXGetFBConfigAttrib get_fb_config_attrib;

			/**
			 * @brief Return visual that is associated with the frame buffer configuration
			 *
			 * @param dpy Specifies the connection to the X server.
			 * @param config Specifies the GLX frame buffer configuration.
			 *
			 * @see https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glXGetVisualFromFBConfig.xml
			 */
			PFN_glXGetVisualFromFBConfig get_visual_from_fb_config;
		};

		
		extern glXExtensions _exts; 	 	///< glX Extensions pointer-to-functions 
		extern glXFuncs _fn;			///< glX functions 
		extern glXExtensionsFlags has; ///< glX Extensions flags

		bool load();
		void unload();
		void * get_proc_address(cstr proc_name);
	} // namespace glx

} // namespace ct

// clang-format off
#define glXQueryExtension(dpy, errorBase, eventBase) ct::glx::_fn.query_extension(dpy, errorBase, eventBase)
#define glXQueryExtensionsString(dpy, screen) ct::glx::_fn.query_extensions_string(dpy, screen)
#define glXQueryVersion(dpy, major, minor) ct::glx::_fn.query_version(dpy, major, minor)

#define glXGetFBConfigs(dpy, screen, nelements) ct::glx::_fn.get_fb_configs(dpy, screen, nelements)
#define glXGetFBConfigAttrib(dpy, config, attribute, value) ct::glx::_fn.get_fb_config_attrib(dpy, config, attribute, value)
#define glXGetClientString(dpy, name) ct::glx::_fn.get_client_string(dpy, name)

#define glXGetProcAddress(proc_name) ct::glx::_fn.get_proc_address(proc_name)

#define glXCreateNewContext(dpy, config, render_type, share_list, direct) ct::glx::_fn.create_new_context(dpy, config, render_type, share_list, direct)
#define glXMakeCurrent(dpy, drawable, ctx) ct::glx::_fn.make_current(dpy, drawable, ctx)
#define glXSwapBuffers(dpy, drawable) ct::glx::_fn.swap_buffers(dpy, drawable)
#define glXCreateWindow(dpy, config, window, attrib_list) ct::glx::_fn.create_window(dpy, config, window, attrib_list)

#define glXGetProcAddressARB(proc_name) ct::glx::_exts.get_proc_address_arb(proc_name)
#define glXCreateContextAttribsARB(dpy, config, share_context, direct, attrib_list) ct::glx::_exts.create_context_attribs_arb(dpy, config, share_context, direct, attrib_list)

// #define glXGetFBConfigAttrib(dpy) ct::_glx.get_fb_config_attrib(dpy)

#endif
