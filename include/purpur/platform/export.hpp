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

#ifndef _PURPURINA_PLATFORM_EXPORTS_HPP_
#define _PURPURINA_PLATFORM_EXPORTS_HPP_

#include <purpur/core/config.hpp>

#ifdef PURPURINA_PLATFORM_EXPORTS
    #define PURPURINA_PLATFORM_API PURPURINA_API_EXPORT
#else
    #define PURPURINA_PLATFORM_API PURPURINA_API_IMPORT
#endif


#endif
