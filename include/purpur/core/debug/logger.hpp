
#ifndef _PURPURINA_FRWK_LOGGER_HPP_
#define _PURPURINA_FRWK_LOGGER_HPP_

#include <iostream>

#include <purpur/core/export.hpp>
#include <purpur/core/debug/loglevel.hpp>

namespace ppr {

	class PURPURINA_CORE_API Logger {

	private:

		void printLevel(LogLevel level);

		template<typename T>
		void print(T only) {
			std::cout << only << std::endl;
		}

		template<typename T, typename... Args>
		void print(T current, Args... next) {
			std::cout << current;

			if (sizeof...(next) > 0) {
				std::cout << ", ";
			}

			print(next...);
		}

	public:

		Logger();

		void log() {
			this->printLevel(LogLevel::Log);
			std::cout << std::endl;
		}

		template<typename... Args>
		void log(Args... args) {
			this->printLevel(LogLevel::Log);
			this->print(args...);
			std::cout << std::endl;
		}






		void error(const char* message, ...);
	};
}


#endif
