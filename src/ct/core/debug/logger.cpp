
#include <cstdarg>
#include <ct/core/debug/logger.hpp>
#include <stdio.h>

namespace ct {

	Logger::Logger() {}

	void Logger::print_level(LogLevel level) {
		std::cout << get_log_level_name(level) << ": ";
	}


} // namespace ct
