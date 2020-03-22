


#include <cstdarg>
#include <stdio.h>

// #include <purpurina/Core/Debug.hpp>
#include <purpurina/Core/Debug/Logger.hpp>

namespace ppr {

		Logger::Logger() {

		}

		void Logger::print(const char* message, const char & argptr) {
			
		}

		template<typename ...Args>
		void Logger::error(const char* message, const Args& ...args) {
			va_list argptr;
			va_start(argptr, message);
			print(message, argptr);
			va_end(argptr);
		}

		void Logger::warn(const char* message, ...) {

		}
		void Logger::info(const char* message, ...) {

		}
	
}
