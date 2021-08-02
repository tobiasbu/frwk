
#ifndef _CHRONOTRIX_FRWK_GLCONTEXT_HPP_
#define _CHRONOTRIX_FRWK_GLCONTEXT_HPP_

#include <ct/core/utils/noncopyable.hpp>
#include <ct/platform/context_config.hpp>
#include <ct/platform/render_types.hpp>

namespace ct {

	class Window;

	namespace internal {

		////////////////////////////////////////////////////////////
		/// @brief Represents abstract rendering context
		///
		////////////////////////////////////////////////////////////
		class ContextImpl : NonCopyable {
		public:
			virtual ~ContextImpl();

			virtual void make_current() = 0;
			virtual void swap_buffers() = 0;

			static ContextImpl * create(Window * window, const ContextConfig & config);

			static get_proc_address_fn get_proc_address(cstr proc_name);
		};

	} // namespace internal

} // namespace ct

#endif
