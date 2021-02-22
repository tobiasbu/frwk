
#ifndef _CHRONOTRIX_FRWK_RENDER_NSGLCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_RENDER_NSGLCONTEXT_HPP_

#include <ct/render/context_impl.hpp>

#ifdef __OBJC__
@class NSOpenGLContext;
typedef NSOpenGLContext * NSOpenGLContextPtr;
// @class NSOpenGLView;
@class NSWindow;
#else
typedef void * NSOpenGLContextPtr;
// typedef void* NSOpenGLView;
typedef void * NSWindow;
#endif

namespace ct {

	class Window;

	namespace internal {

		class NsGlContext final : public ContextImpl {
		private:
			NSOpenGLContextPtr context;
			Window * owner;

		public:
			NsGlContext() = delete;
			~NsGlContext();
			NsGlContext(NSOpenGLContextPtr context, Window * owner);

			void make_current() override;
			void swap_buffers() override;

			static NsGlContext * create(Window * window, const ContextConfig & config);
			static glGetProcAddressCb get_proc_address(cstr procname);
		};

	} // namespace internal

} // namespace ct

#endif
