
#include <ct/render/render.hpp>
#include <ct/render/opengl/wgl_context.hpp>
#include <ct/render/win32/win32_internal.hpp>

namespace ct {

	namespace Render {

		bool init() {

			if (!internal::create_helper_window()) {
				return false;
			}

			return true;
		}

		bool terminate() {
			internal::destroy_helper_window();
			return true;
		}

		getProcAddressCb get_proc_address(cstr procname) {
			return internal::WglContext::get_proc_address(procname);
		}

	}

}
