////////////////////////////////////////////////////////////
/// Chronotrix Framework
///
/// \todo Copyright notice
///
////////////////////////////////////////////////////////////
///
/// \ingroup chronotrix-platform
/// \file Export.hpp
/// \author Tobias Ulrich <tobiasbulrich@gmail.com>
/// \date January 23, 2021
///
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_PLATFORM_EXPORTS_HPP_
#define _CHRONOTRIX_FRWK_PLATFORM_EXPORTS_HPP_

#include <ct/core/config/api.hpp>

#ifdef CHRONOTRIX_PLATFORM_EXPORTS
	#define CT_PLATFORM_API CT_API_EXPORT
#else
	#define CT_PLATFORM_API CT_API_IMPORT
#endif

#endif
