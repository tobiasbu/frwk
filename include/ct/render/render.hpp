
#ifndef _CHRONOTRIX_FRWK_RENDER_HPP_
#define _CHRONOTRIX_FRWK_RENDER_HPP_

#include <ct/render/export.hpp>
#include <ct/render/render_types.hpp>

namespace ct {

	namespace Render {

		CT_RENDER_API bool init();

		CT_RENDER_API bool terminate();

		CT_RENDER_API extern const get_proc_address_fn_ptr get_proc_address;

	} // namespace Render

} // namespace ct

#endif
