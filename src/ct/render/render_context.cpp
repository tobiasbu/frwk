
#include <ct/render/context_impl.hpp>
#include <ct/render/render_context.hpp>

namespace ct {

	RenderContext::RenderContext(internal::ContextImpl * _impl) : impl(_impl) {}

	void RenderContext::make_current() {
		if (impl) {
			impl->make_current();
		}
	}

	void RenderContext::swap_buffers() {
		if (impl) {
			impl->swap_buffers();
		}
	}

	RenderContext * RenderContext::create(Window * window, const ContextConfig & config) {
		auto impl = internal::ContextImpl::create(window, config);

		return new RenderContext(impl);
	}

} // namespace ct
