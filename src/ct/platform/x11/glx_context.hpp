
#ifndef _CHRONOTRIX_FRWK_GLXCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_GLXCONTEXT_HPP_

#include <ct/platform/context_impl.hpp>
#include <ct/platform/x11/glx_lib.hpp>

namespace ct {

	class Window;

	namespace internal {

		class GlxContext final : public ContextImpl {
		private:
			GLXWindow glx_window;
			GLXContext glx_context;

		public:
			explicit GlxContext(GLXContext glx_context, GLXWindow glx_window);

			void make_current() override;
			void swap_buffers() override;

			static GlxContext * create(Window * window, const ContextConfig & config);
		};

	} // namespace internal

} // namespace ct

#endif
