
#include <ct/render/render_context.hpp>
#include <ct/render/context_impl.hpp>

namespace ct {

	RenderContext::RenderContext(internal::ContextImpl * impl)
	:
	impl(impl)
	{}

	RenderContext* RenderContext::create(Window* window, const ContextConfig & config) {

		auto impl = internal::ContextImpl::create(window, config);

		return new RenderContext(impl);

	}

}
