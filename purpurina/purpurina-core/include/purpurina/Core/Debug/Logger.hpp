
#ifndef _PURPURINA_LOGGER_HPP_
#define _PURPURINA_LOGGER_HPP_

#include <purpurina/Core/Export.hpp>

namespace ppr {

	class PURPURINA_CORE_API Logger {

	private:

		
		/*void print(const char* message, const char & argptr);*/

	public:
		Logger();
		void print(const char* message);
		/*template<typename ...Args>
		void error(const char* message, const Args& ...args);

		void warn(const char* message, ...);
		void info(const char* message, ...);*/
	};
}


#endif
