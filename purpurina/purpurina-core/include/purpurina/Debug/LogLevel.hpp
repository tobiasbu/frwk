
#ifndef _PURPURINA_LOG_LEVEL_HPP_
#define _PURPURINA_LOG_LEVEL_HPP_

#include <purpurina/Config.hpp>

namespace ppr {

	enum class LogLevel {
		Log = 32,
		Debug = 64,
		Warning = 128,
		Error = 256,
		Fatal = 512
	};

	const char * getLogLevelName(LogLevel level) {
		switch (level)
		{
			case LogLevel::Debug: return "Debug";
			default: return "Log";
		}
	}
}


#endif
