
#ifndef _CHRONOTRIX_FRWK_RENDER_TYPES_HPP_
#define _CHRONOTRIX_FRWK_RENDER_TYPES_HPP_

#include <ct/config/types.hpp>

namespace ct {

	// typedef void (*get_proc_address_fn)(void);
	// typedef get_proc_address_fn (*get_proc_address_fn_ptr)(cstr procname);
	using PFN_get_proc_address = void * (*)(cstr proc_name);

} // namespace ct

#endif
