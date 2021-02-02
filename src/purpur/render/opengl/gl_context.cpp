
#include <purpur/core/config.hpp>
#include <purpur/render/opengl/gl_context.hpp>

#ifdef PPR_OS_WIN32
	#include <purpur/render/opengl/wgl_context.hpp>
	typedef  ppr::internal::WglContext GlContextType;
#endif

namespace ppr {

#ifndef PPR_OS_MACOS

	/**
	 * \brief Create OpenGL context
	 */
	std::unique_ptr<GlContext> GlContext::create() {

		GlContext* context = nullptr;

		context = new GlContextType();

		return std::unique_ptr<GlContext>(context);

	}

#endif


}
