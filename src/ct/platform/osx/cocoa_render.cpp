
#include <ct/platform/context_impl.hpp>
#include <ct/platform/render.hpp>

namespace ct {

	namespace Render {

		bool init() {
			return true;
		}

		bool terminate() {
			return true;
		}

		getProcAddressCb get_proc_address(cstr procname) {
			return ct::internal::ContextImpl::get_proc_address(procname);
		}

	} // namespace Render

} // namespace ct
