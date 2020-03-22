#ifndef _PURPURINA_LOG_HPP_
#define _PURPURINA_LOG_HPP_

namespace ppr {

	class Log {
		private:
			Log();

		public:
			void error(const char* message);
			void warn(const char* message);
			void info(const char* message);
	};
}


#endif
