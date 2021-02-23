
#include <ct/render/render.hpp>
#include <ct/render/opengl/win32_internal.hpp>

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

	}

}
