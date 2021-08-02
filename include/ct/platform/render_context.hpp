
#ifndef _CHRONOTRIX_FRWK_RENDER_RENDERCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_RENDER_RENDERCONTEXT_HPP_

#include <ct/platform/context_config.hpp>
#include <ct/platform/export.hpp>

namespace ct {

	class Window;
	namespace internal {
		class ContextImpl;
	}

	class CT_PLATFORM_API RenderContext {
	private:
		internal::ContextImpl * impl;

	public:
		RenderContext(internal::ContextImpl * impl);

		void make_current();
		void swap_buffers();

		static RenderContext * create();
		static RenderContext * create(Window * window, const ContextConfig & config);
	};

} // namespace ct

#endif
