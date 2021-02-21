
#include <ct/core/config/os_detection.hpp>
#include <ct/render/context_impl.hpp>

#if defined(CT_OS_WINDOWS)

	#include <ct/render/opengl/wgl_context.hpp>
	typedef ct::internal::WglContext ContextType;

#endif

namespace ct {

	namespace internal {

		ContextImpl::~ContextImpl() {};

		ContextImpl* ContextImpl::create(Window* window, const ContextConfig & config) {
			return ContextType::create(window);
		}

	}

}
