
#include <ct/platform/context_impl.hpp>
#include <ct/platform/render_context.hpp>

#if defined(CT_OS_WINDOWS)

	#include <ct/platform/win32/wgl_context.hpp>
	using ContextType = ct::internal::WglContext;

#elif defined(CT_OS_MACOS)

	#include <ct/platform/osx/nsgl_context.hpp>
	using ContextType = typedef ct::internal::NsGlContext;

#elif defined(CT_OS_LINUX)

	#include <ct/platform/x11/glx_context.hpp>
	using ContextType = ct::internal::GlxContext;

#endif


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

	RenderContext * RenderContext::create(internal::WindowImpl * window, const ContextConfig & config) {
		auto impl = ContextType::create(window, config);

		return new RenderContext(impl);
	}

} // namespace ct
