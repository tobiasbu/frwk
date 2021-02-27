
#ifndef _CHRONOTRIX_FRWK_RENDER_TYPES_HPP_
#define _CHRONOTRIX_FRWK_RENDER_TYPES_HPP_

#include <ct/core/types.hpp>

namespace ct {

	typedef void (*get_proc_address_fn)(void);
	typedef get_proc_address_fn (*get_proc_address_fn_ptr)(cstr procname);

} // namespace ct

#endif
