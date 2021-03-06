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

#ifndef _CHRONOTRIX_FRWK_RENDER_EXPORTS_HPP_
#define _CHRONOTRIX_FRWK_RENDER_EXPORTS_HPP_

#include <ct/config/api_export.hpp>

#ifdef CTFK_RENDER_EXPORTS
	#define CT_RENDER_API CT_API_EXPORT
#else
	#define CT_RENDER_API CT_API_IMPORT
#endif

#endif
