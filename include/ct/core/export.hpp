////////////////////////////////////////////////////////////
/// Chronotrix Framework
///
/// \todo Copyright notice
///
////////////////////////////////////////////////////////////
///
/// \ingroup chronotrix-core
/// \file Export.hpp
/// \author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// \date March 22, 2020
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
