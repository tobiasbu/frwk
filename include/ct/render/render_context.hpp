
#ifndef _CHRONOTRIX_FRWK_RENDER_RENDERCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_RENDER_RENDERCONTEXT_HPP_

#include <ct/render/export.hpp>
#include <ct/render/context_config.hpp>

namespace ct {

	class Window;
	namespace internal {
		class ContextImpl;
	}

	class CT_RENDER_API RenderContext {

		private:

		internal::ContextImpl * impl;

		public:

		RenderContext(internal::ContextImpl * impl);

		static RenderContext * create();
		static RenderContext * create(Window* window, const ContextConfig & config);

	};

}

#endif
