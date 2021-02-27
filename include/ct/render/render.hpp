
#ifndef _CHRONOTRIX_FRWK_RENDER_HPP_
#define _CHRONOTRIX_FRWK_RENDER_HPP_

#include <ct/render/export.hpp>
#include <ct/render/render_types.hpp>

namespace ct {

	namespace Render {

		CT_RENDER_API bool init();

		CT_RENDER_API bool terminate();

		CT_RENDER_API getProcAddressCb get_proc_address(cstr procname);

	} // namespace Render

} // namespace ct

#endif
