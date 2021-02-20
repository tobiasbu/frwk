
#include <ct/core/config.hpp>
#include <ct/render/opengl/gl_context.hpp>

#ifdef CT_OS_WIN32
	#include <ct/render/opengl/wgl_context.hpp>
typedef ct::internal::WglContext GlContextType;
#endif

namespace ct {

#ifndef CT_OS_MACOS

	/**
	 * \brief Create OpenGL context
	 */
	std::unique_ptr<GlContext> GlContext::create() {
		GlContext * context = nullptr;

		context = new GlContextType();

		return std::unique_ptr<GlContext>(context);
	}

#endif

} // namespace ct
