
#include <dlfcn.h>
#include <cstring>
#include <iostream>

#include <ct/platform/x11/x11.hpp>
#include <ct/platform/x11/glx_lib.hpp>

namespace ct {

	namespace glx {

		void * handle;      ///< gLX library handle
		i32 major_version;  ///< Major version o glX
		i32 minor_version;  ///< Minor version o glX

		glXExtensions _exts = {0};
		glXFuncs _fn = {0};
		glXExtensionsFlags has = {0};


		bool is_supported(cstr extension_name, cstr glx_extensions) {
			cstr start = glx_extensions;
			cstr pos;
			cstr end = CT_NULLPTR;
			size_t size;

			while (true) {
				pos = strstr(start, extension_name);
				if (!pos) {
					return false;
				}

				if (end == CT_NULLPTR) {
					size = strlen(extension_name);
				}
				end = pos + size;

				if (pos == start || *(pos - 1) == ' ') {
					if (*end == ' ' || *end == '\0') {
						break;
					}
				}

				start = end;
			}
			return true;
		}

		void * get_proc_address(cstr proc_name) {
			if (_fn.get_proc_address) {
				return _fn.get_proc_address((ucstr)proc_name);
			} else if (_exts.get_proc_address_arb) {
				return _exts.get_proc_address_arb((ucstr)proc_name);
			}
			return dlsym(handle, proc_name);
		}

		bool load() {
			if (handle) {
				return true;
			}

			cstr so_names[] = {
			    "libGL.so.1",
			    "libGL.so",
			};

			void * lib = CT_NULLPTR;

			for (auto && so: so_names) {
				lib = dlopen(so, RTLD_LAZY | RTLD_LOCAL);
				if (lib != CT_NULLPTR) {
					break;
				}
			}

			if (!lib) {
				return false;
			}

			handle = lib;

			// clang-format off

			_fn.get_proc_address = (PFN_glXGetProcAddress)dlsym(lib, "glXGetProcAddress");
			_exts.get_proc_address_arb = (PFN_glXGetProcAddressARB)dlsym(lib, "glXGetProcAddressARB");

			// Client
			_fn.get_client_string = (PFN_glXGetClientString)dlsym(lib, "glXGetClientString");
			_fn.query_extension = (PFN_glXQueryExtension)dlsym(lib, "glXQueryExtension");
			_fn.query_extensions_string = (PFN_glXQueryExtensionsString)dlsym(lib, "glXQueryExtensionsString");
			_fn.query_version = (PFN_glXQueryVersion)dlsym(lib, "glXQueryVersion");

			// Render area
			_fn.create_window = (PFN_glXCreateWindow)dlsym(lib, "glXCreateWindow");
			_fn.destroy_window = (PFN_glXDestroyWindow)dlsym(lib, "glXDestroyWindow");

			// Context
			_fn.create_new_context = (PFN_glXCreateNewContext)dlsym(lib, "glXCreateNewContext");
			_fn.destroy_context = (PFN_glXDestroyContext)dlsym(lib, "glXDestroyContext");
			_fn.make_current = (PFN_glXMakeCurrent)dlsym(lib, "glXMakeCurrent");
			_fn.swap_buffers = (PFN_glXSwapBuffers)dlsym(lib, "glXSwapBuffers");

			// Framebuffer
			_fn.get_fb_configs = (PFN_glXGetFBConfigs)dlsym(lib, "glXGetFBConfigs");
			_fn.get_fb_config_attrib = (PFN_glXGetFBConfigAttrib)dlsym(lib, "glXGetFBConfigAttrib");
			_fn.get_visual_from_fb_config = (PFN_glXGetVisualFromFBConfig)dlsym(lib, "glXGetVisualFromFBConfig");

			// clang-format on

			if (!_fn.get_proc_address || !_fn.get_client_string || !_fn.query_extension ||
			    !_fn.query_version || !_fn.create_window || !_fn.destroy_window ||
			    !_fn.create_new_context || !_fn.make_current || !_fn.destroy_context ||
			    !_fn.get_fb_config_attrib || !_fn.get_fb_configs ||
			    !_fn.get_visual_from_fb_config) {
				return false;
			}

			// Query GLX version
			if (!glXQueryVersion(x11::display, &major_version, &minor_version)) {
				// Failed to query GLX version
				return false;
			}

			// Check if extension is supported
			int errorBase, eventBase;
			bool support_glx_extension =
			    glXQueryExtension(x11::display, &errorBase, &eventBase) == True ? true : false;

			// Check extensions
			if (support_glx_extension) {
				cstr glx_exts = glXQueryExtensionsString(x11::display, x11::screen);

				// First at all check if we really have glXGetProcAddressARB
				if (!_exts.get_proc_address_arb) {
					if (is_supported(CT_STRINGER(ARB_get_proc_address), glx_exts)) {
						_exts.get_proc_address_arb =
						    (PFN_glXGetProcAddressARB)glXGetProcAddress(
						        (ucstr) "glXGetProcAddressARB");
					}
				}
				has.ARB_get_proc_address = !!_exts.get_proc_address_arb;

				// clang-format off

				// Get other extensions
				#define CtIsGlxExtensionSupported(ext_name)	         								\
					has.ext_name = is_supported(CT_STRINGER(CT_JOIN(GLX_, ext_name)), glx_exts);    \
		

				#define CtIsGlxExtensionProcSupported(ext_name, proc_name, ct_func_name) 							\
					if (is_supported(CT_STRINGER(CT_JOIN(GLX_, ext_name)), glx_exts)) { 			    			\
						_exts.ct_func_name = (CT_JOIN(PFN_, proc_name))get_proc_address(CT_STRINGER(proc_name));	\
						has.ext_name = !!_exts.ct_func_name;                     									\
					} else {                                                             							\
						has.ext_name = false;                    													\
					}

					CtIsGlxExtensionProcSupported(EXT_swap_control, glXSwapIntervalEXT, swap_interval_ext)
					CtIsGlxExtensionProcSupported(SGI_swap_control, glXSwapIntervalSGI, swap_interval_sgi)
					CtIsGlxExtensionProcSupported(MESA_swap_control, glXSwapIntervalMESA, swap_interval_mesa)
					CtIsGlxExtensionProcSupported(ARB_create_context, glXCreateContextAttribsARB, create_context_attribs_arb)

					CtIsGlxExtensionSupported(EXT_visual_info)
					CtIsGlxExtensionSupported(EXT_visual_rating)
					CtIsGlxExtensionSupported(EXT_import_context)
					CtIsGlxExtensionSupported(EXT_swap_control_tear)
					CtIsGlxExtensionSupported(EXT_texture_from_pixmap)
					CtIsGlxExtensionSupported(EXT_buffer_age)
					CtIsGlxExtensionSupported(EXT_create_context_es_profile)
					CtIsGlxExtensionSupported(EXT_create_context_es2_profile)
					CtIsGlxExtensionSupported(EXT_stereo_tree)
					CtIsGlxExtensionSupported(EXT_framebuffer_sRGB)

					CtIsGlxExtensionSupported(SGIX_fbconfig)
					CtIsGlxExtensionSupported(SGIX_pbuffer)
					CtIsGlxExtensionSupported(SGI_video_sync)

					CtIsGlxExtensionSupported(NV_delay_before_swap)
					CtIsGlxExtensionSupported(NV_robustness_video_memory_purge)
					CtIsGlxExtensionSupported(NV_float_buffer)
					CtIsGlxExtensionSupported(NV_multisample_coverage)
					CtIsGlxExtensionSupported(NV_copy_image)

					CtIsGlxExtensionSupported(ARB_create_context_profile)
					CtIsGlxExtensionSupported(ARB_create_context_no_error)
					CtIsGlxExtensionSupported(ARB_create_context_robustness)
					CtIsGlxExtensionSupported(ARB_context_flush_control)
					CtIsGlxExtensionSupported(ARB_multisample)
					CtIsGlxExtensionSupported(ARB_fbconfig_float)

					#undef CtIsGlxExtensionSupported
					#undef CtIsGlxExtensionProcSupported
				// clang-format on
			}

			return true;
		}

		void unload() {
			if (handle) {
				dlclose(handle);
				handle = CT_NULLPTR;
			}
		}

	} // namespace glx

} // namespace ct
