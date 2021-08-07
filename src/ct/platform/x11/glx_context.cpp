
#include <ct/platform/window.hpp>
#include <ct/platform/x11/x11.hpp>

#include <ct/platform/x11/glx_context.hpp>

namespace ct {

	class Window;

	namespace internal {

		namespace detail {
			GLXContext create_legacy_context(GLXFBConfig fbconfig, GLXContext shared_context) {
				return glXCreateNewContext(
				    x11::display, fbconfig, GLX_RGBA_TYPE, shared_context, True);
			}

			i32 get_fb_config_attrib(GLXFBConfig config, int attrib) {
				i32 result;
				glXGetFBConfigAttrib(x11::display, config, attrib, &result);
				return result;
			}

			GLXFBConfig create_fb_config(const ContextConfig & config) {
				i32 nelements = 0;
				GLXFBConfig * glx_fbconfigs =
				    glXGetFBConfigs(x11::display, x11::screen, &nelements);

				if (!glx_fbconfigs || !nelements) {
					return CT_NULLPTR;
				}

				ContextConfig configs;

				for (i32 i = 0; i < nelements; i += 1) {
					const GLXFBConfig current = glx_fbconfigs[i];

					// ignore GLX_COLOR_INDEX_BIT - only RGBA
					if (!(get_fb_config_attrib(current, GLX_RENDER_TYPE) & GLX_RGBA_BIT)) {
						continue;
					}

					// // consider configurations only for windows
					// if (!(get_glx_fb_config_attrib(current, GLX_DRAWABLE_TYPE) & GLX_WINDOW_BIT)) {
					// 	continue;
					// }

					if ((bool)get_fb_config_attrib(current, GLX_DOUBLEBUFFER) !=
					    config.double_buffer) {
						continue;
					}

					// TODO(@tobiasbu) create best pixel format selector
					// configs.alpha_bits = get_fb_config_attrib(current, GLX_ALPHA_SIZE);
					// configs.depth_bits = get_fb_config_attrib(current, GLX_DEPTH_SIZE);
					// configs.stencil_bits = get_fb_config_attrib(current, GLX_STENCIL_SIZE);

					return current;
				}
			}
		} // namespace detail

		GlxContext::GlxContext(GLXContext glx_context, GLXWindow glx_window)
		: glx_context(glx_context),
		  glx_window(glx_window) {}

		void GlxContext::make_current() {
			glXMakeCurrent(x11::display, glx_window, glx_context);
		}

		void GlxContext::swap_buffers() {
			glXSwapBuffers(x11::display, glx_window);
		}

		GlxContext * GlxContext::create(Window * window, const ContextConfig & config) {
			GLXFBConfig fbconfig = detail::create_fb_config(config);
			if (!fbconfig) {
				return CT_NULLPTR;
			}

			auto window_handle = window->get_handle();
			GLXContext shared_context;
			GLXContext glx_context;

			// TODO(@tobiasbu) OpenGL ES profile
			// if (config.client == RendererClient.OpenGL_ES)

			if (config.forward) {
				if (!glx::has.ARB_create_context) {
					return CT_NULLPTR;
				}
			}

			if (config.profile) {
				if (!glx::has.ARB_create_context ||
				    !glx::has.ARB_create_context_profile) {
					return CT_NULLPTR;
				}
			}

			i32 attrib_index = 0;
			i32 attribs[18];

			x11::catch_error_handler();

			if (glx::has.ARB_create_context) {
				i32 flags = 0;
				i32 mask = 0;

				// For OpenGL client
				// TODO(@tobiasbu) forwar flag
				// if (config.forward) {
				// 	flags |= GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
				// }

				// TODO(@tobiasbu) core/compatibility profiles mask
				// if (config.profile == ) mask |= GLX_CONTEXT_CORE_PROFILE_BIT_ARB;
				// mask |= GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

				// debug
				// TODO(@tobiasbu) debug mask
				// mask != GLX_CONTEXT_DEBUG_BIT_ARB;

				// robustness
				if (glx::has.ARB_create_context_robustness) {
					// TODO(@tobiasbu) robustness
					// GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB = GLX_NO_RESET_NOTIFICATION_ARB
					// GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB = GLX_LOSE_CONTEXT_ON_RESET_ARB
					// flags |= GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB;
				}

				// release
				if (glx::has.ARB_context_flush_control) {
					// TODO(@tobiasbu) flush control
					// GLX_CONTEXT_RELEASE_BEHAVIOR_ARB = GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB
					// LX_CONTEXT_RELEASE_BEHAVIOR_ARB = GLX_CONTEXT_RELEASE_BEHAVIOR_ARB
				}

				// no error
				if (glx::has.ARB_create_context_no_error) {
					// TODO(@tobiasbu) No error
					// GLX_CONTEXT_OPENGL_NO_ERROR_ARB = 1
				}

				if (config.major_version != 1 || config.minor_version != 0) {
					attribs[attrib_index++] = GLX_CONTEXT_MAJOR_VERSION_ARB;
					attribs[attrib_index++] = config.major_version;

					attribs[attrib_index++] = GLX_CONTEXT_MINOR_VERSION_ARB;
					attribs[attrib_index++] = config.minor_version;
				}

				if (mask) {
					attribs[attrib_index++] = GLX_CONTEXT_PROFILE_MASK_ARB;
					attribs[attrib_index++] = mask;
				}

				if (flags) {
					attribs[attrib_index++] = GLX_CONTEXT_FLAGS_ARB;
					attribs[attrib_index++] = flags;
				}

				attribs[attrib_index++] = None;
				attribs[attrib_index++] = None;

				glx_context = glXCreateContextAttribsARB(
				    x11::display, fbconfig, shared_context, True, attribs);

				// TODO(@tobiasbu) Fallback for mesa
				if (!glx_context) {
					glx_context = detail::create_legacy_context(NULL, NULL);
				}

			} else {
				// legacy OpenGL context
				glx_context = detail::create_legacy_context(NULL, NULL);
			}

			x11::release_error_handler();

			if (!glx_context) {
				return CT_NULLPTR;
			}

			auto glx_window = glXCreateWindow(x11::display, fbconfig, window_handle, NULL);
			if (!glx_window) {
				return CT_NULLPTR;
			}

			return new GlxContext(glx_context, glx_window);

		} // namespace internal

	} // namespace internal

} // namespace ct
