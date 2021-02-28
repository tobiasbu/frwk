////////////////////////////////////////////////////////////
/// Chronotrix Framework
///
/// \todo Copyright notice
///
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_CORE_EXPORTS_HPP_
#define _CHRONOTRIX_FRWK_CORE_EXPORTS_HPP_

#include <ct/core/config/api.hpp>

#ifdef CHRONOTRIX_CORE_EXPORTS
	#define CT_CORE_API CT_API_EXPORT
#else
	#define CT_CORE_API CT_API_IMPORT
#endif

#endif
