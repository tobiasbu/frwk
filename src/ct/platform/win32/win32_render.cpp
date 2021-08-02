
#include <ct/platform/opengl/wgl_context.hpp>
#include <ct/platform/render.hpp>
#include <ct/platform/win32/win32_internal.hpp>

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

		const get_proc_address_fn_ptr get_proc_address = internal::WglContext::get_proc_address;

	} // namespace Render

} // namespace ct
