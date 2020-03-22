
#ifndef _PURPURINA_LOGGER_HPP_
#define _PURPURINA_LOGGER_HPP_

namespace ppr {

	class Logger {

	private:

		void print(const char* message, const char & argptr);

	public:
		Logger();

		template<typename ...Args>
		void error(const char* message, const Args& ...args);

		void warn(const char* message, ...);
		void info(const char* message, ...);
	};
}


#endif
