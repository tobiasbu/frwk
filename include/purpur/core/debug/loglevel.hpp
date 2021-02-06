
#ifndef _PURPURINA_FRWK_LOG_LEVEL_HPP_
#define _PURPURINA_FRWK_LOG_LEVEL_HPP_

#include <purpur/core/types.hpp>

namespace ppr {

	enum class LogLevel : uint32
	{
		Log = 32,
		Debug = 64,
		Warning = 128,
		Error = 256,
		Fatal = 512
	};

	const char * getLogLevelName(LogLevel level) {
		switch (level) {
			case LogLevel::Debug: return "Debug";
			default: return "Log";
		}
	}
} // namespace ppr

#endif
