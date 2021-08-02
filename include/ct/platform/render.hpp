
#ifndef _CHRONOTRIX_FRWK_RENDER_HPP_
#define _CHRONOTRIX_FRWK_RENDER_HPP_

#include <ct/platform/export.hpp>
#include <ct/platform/render_types.hpp>

namespace ct {

	/// Render module
	namespace Render {

		CT_PLATFORM_API bool init();

		CT_PLATFORM_API bool terminate();

		CT_PLATFORM_API extern const get_proc_address_fn_ptr get_proc_address;

	} // namespace Render

} // namespace ct

#endif
