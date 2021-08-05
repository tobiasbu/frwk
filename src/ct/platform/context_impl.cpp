
#include <ct/config/os.hpp>
#include <ct/platform/context_impl.hpp>

#if defined(CT_OS_WINDOWS)

	#include <ct/platform/win32/wgl_context.hpp>
typedef ct::internal::WglContext ContextType;

#elif defined(CT_OS_MACOS)

	#include <ct/platform/osx/nsgl_context.hpp>
typedef ct::internal::NsGlContext ContextType;

#elif defined(CT_OS_LINUX)

	#include <ct/platform/x11/glx_context.hpp>
typedef ct::internal::GlxContext ContextType;

#endif

namespace ct {

	namespace internal {

		ContextImpl::~ContextImpl() {};

		PFN_get_proc_address ContextImpl::get_proc_address(cstr proc_name) {
			return ContextType::get_proc_address(proc_name);
		}

		ContextImpl * ContextImpl::create(Window * window, const ContextConfig & config) {
			return ContextType::create(window, config);
		}

	} // namespace internal

} // namespace ct
