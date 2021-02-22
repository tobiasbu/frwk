
#include <ct/platform/detail/win32_detail.hpp>

struct HWND__;

namespace ct {

	namespace internal {

		bool create_helper_window();

		void destroy_helper_window();

		HWND__* get_helper_window();

	}

}

