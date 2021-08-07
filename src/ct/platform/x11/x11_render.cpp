
#include <dlfcn.h>
#include <X11/Xlib.h>

#include <ct/config.hpp>
#include <ct/platform/x11/glx_lib.hpp>

#include <ct/platform/render.hpp>

namespace ct {

	/// Render module
	namespace Render {
		bool init() {
			if (!glx::load()) {
				return false;
			}

			return true;
		}

		bool terminate() {
			glx::unload();

			return true;
		}

		const PFN_get_proc_address get_proc_address = glx::get_proc_address;

	} // namespace Render

} // namespace ct
