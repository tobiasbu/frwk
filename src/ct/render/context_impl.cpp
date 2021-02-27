
#include <ct/core/config/os_detection.hpp>
#include <ct/render/context_impl.hpp>
#include <stdio.h>

#if defined(CT_OS_WINDOWS)

	#include <ct/render/opengl/wgl_context.hpp>
typedef ct::internal::WglContext ContextType;

#elif defined(CT_OS_MACOS)

	#include <ct/render/opengl/nsgl_context.hpp>
typedef ct::internal::NsGlContext ContextType;

#endif

namespace ct {

	namespace internal {

		ContextImpl::~ContextImpl() {};

		getProcAddressCb ContextImpl::get_proc_address(cstr proc_name) {
			return ContextType::get_proc_address(proc_name);
		}

		ContextImpl * ContextImpl::create(Window * window, const ContextConfig & config) {
			return ContextType::create(window, config);
		}

	} // namespace internal

} // namespace ct
