////////////////////////////////////////////////////////////
// Purpurina Engine
//
// \todo Copyright notice
//
////////////////////////////////////////////////////////////
///
/// \ingroup purpurina-core
/// \file AssertHandler.hpp
/// \author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// \date September 25, 2020
///
////////////////////////////////////////////////////////////

#ifndef _PURPURINA_ASSERT_HANDLER_HPP_
#define _PURPURINA_ASSERT_HANDLER_HPP_

#include <purpurina/export.hpp>
#include <purpurina/config.hpp>

#if defined(_MSC_VER) && !defined(_CPPUNWIND)
	#ifndef (PURPURINA_ASSERT_CUSTOM_THROW)
		#define PURPURINA_ASSERT_CUSTOM_THROW
	#endif
#endif


namespace ppr {
	namespace internal {
		namespace Assert {

			enum class Action {
				None,
				Ignore,
				Break,
				Throw,
				Abort,
			};

			enum class Level {
				Warning = 8,
				Debug = 16,
				Error = 32,
				Fatal = 64
			};

			PURPURINA_CORE_API Action getAction(Level level = Level::Error, bool* ignore = PPR_NULLPTR);

			PURPURINA_CORE_API cstr handle(cstr file,
										   int32 line,
										   cstr function,
										   cstr expression,
										   bool* ignore,
										   cstr message, ...);

			PURPURINA_CORE_API bool ignoreAllAsserts();
		}
	}
}

#endif
