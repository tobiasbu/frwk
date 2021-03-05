
#ifndef _CHRONOTRIX_FRWK_LOGGER_HPP_
	#define _CHRONOTRIX_FRWK_LOGGER_HPP_

	#include <ct/core/debug/loglevel.hpp>
	#include <ct/core/export.hpp>
	#include <iostream>

namespace ct {

	class CT_CORE_API Logger {
	private:
		void print_level(LogLevel level);

		template <typename T>
		void print(T only) {
			std::cout << only;
		}

		template <typename T, typename... Args>
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
			this->print_level(LogLevel::Log);
			std::cout << std::endl;
		}

		template <typename... Args>
		void log(Args... args) {
			this->print_level(LogLevel::Log);
			this->print(args...);
			std::cout << std::endl;
		}

		void error(const char * message, ...);
	};
} // namespace ct

#endif

////////////////////////////////////////////////////////////
/// @class ct::Logger
/// @ingroup core
///
/// Detailed description goes here
///
////////////////////////////////////////////////////////////
