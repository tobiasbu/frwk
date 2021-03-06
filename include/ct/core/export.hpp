////////////////////////////////////////////////////////////
/// Chronotrix Framework
///
/// @todo Copyright notice
///
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_CORE_EXPORTS_HPP_
#define _CHRONOTRIX_FRWK_CORE_EXPORTS_HPP_

#include <ct/config/api_export.hpp>

#ifdef CTFK_CORE_EXPORTS
	#define CT_CORE_API CT_API_EXPORT
#else
	#define CT_CORE_API CT_API_IMPORT
#endif

#endif
