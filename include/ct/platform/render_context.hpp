
#ifndef _CHRONOTRIX_FRWK_RENDER_RENDERCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_RENDER_RENDERCONTEXT_HPP_

#include <ct/platform/context_config.hpp>
#include <ct/platform/export.hpp>

namespace ct {

	namespace internal {
		class ContextImpl;
		class WindowImpl;
	}

	class CT_PLATFORM_API RenderContext {
	private:
		internal::ContextImpl * impl;

	public:
		RenderContext(internal::ContextImpl * impl);

		void make_current();
		void swap_buffers();

		static RenderContext * create();
		static RenderContext * create(internal::WindowImpl * impl, const ContextConfig & config);
	};

} // namespace ct

#endif
