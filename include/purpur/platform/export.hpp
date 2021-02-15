////////////////////////////////////////////////////////////
/// Purpurina Engine
///
/// \todo Copyright notice
///
////////////////////////////////////////////////////////////
///
/// \ingroup purpurina-platform
/// \file Export.hpp
/// \author Tobias Ulrich <tobiasbulrich@gmail.com>
/// \date January 23, 2021
///
////////////////////////////////////////////////////////////

#ifndef _PURPURINA_FRWK_PLATFORM_EXPORTS_HPP_
#define _PURPURINA_FRWK_PLATFORM_EXPORTS_HPP_

#include <purpur/core/config/api.hpp>

#ifdef PURPURINA_PLATFORM_EXPORTS
	#define PPR_PLATFORM_API PPR_API_EXPORT
#else
	#define PPR_PLATFORM_API PPR_API_IMPORT
#endif

#endif
