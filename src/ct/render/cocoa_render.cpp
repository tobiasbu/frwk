
#include <ct/render/context_impl.hpp>
#include <ct/render/render.hpp>

namespace ct {

	namespace Render {

		bool init() {
			return true;
		}

		bool terminate() {
			return true;
		}

		glGetProcAddressCb get_proc_address(cstr procname) {
					return ct::internal::ContextImpl::get_proc_address(procname);
		}

	} // namespace Render

} // namespace ct
