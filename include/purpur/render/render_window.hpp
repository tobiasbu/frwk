
#ifndef _PURPURINA_FRWK_RENDER_WINDOW_HPP_
#define _PURPURINA_FRWK_RENDER_WINDOW_HPP_

#include <purpur/platform/window.hpp>

#include <purpur/render/export.hpp>

namespace ppr {

	class PPR_RENDER_API RenderWidow : public Window {

		public:

			RenderWidow(internal::NativeWindow * nativeWindow);
			static RenderWidow * create();

	};

}

#endif
