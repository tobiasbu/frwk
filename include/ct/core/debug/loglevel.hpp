
#ifndef _CHRONOTRIX_FRWK_LOG_LEVEL_HPP_
#define _CHRONOTRIX_FRWK_LOG_LEVEL_HPP_

#include <ct/core/types.hpp>

namespace ct {

	enum class LogLevel : u32
	{
		Log = 32,
		Debug = 64,
		Warning = 128,
		Error = 256,
		Fatal = 512
	};

	const char * get_log_level_name(LogLevel level) {
		switch (level) {
			case LogLevel::Debug: return "Debug";
			default: return "Log";
		}
	}
} // namespace ct

#endif
