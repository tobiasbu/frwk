
#include <purpurina/Debug/Assert.hpp>


#include <stdarg.h>
#include <stdio.h>
#include <cstdarg> // va_start() and va_end()
#include <sstream>
#include <iostream>

namespace ppr {
	namespace priv {

		void handleAssert(const char* expression, const char* file, int line, const char* message, ...) {


			char messageBuffer[PURPURINA_ASSERT_BUFFER_SIZE] = "";

			if (message)
			{
				va_list argptr;
				va_start(argptr, message);
				vsnprintf(messageBuffer, PURPURINA_ASSERT_BUFFER_SIZE, message, argptr);
				va_end(argptr);
			}

			std::stringstream ss;
			ss << "\nAssertion thrown!" << '\n';
			ss << "Expression: " << expression << '\n';
			ss << "File: " << file << '\n';
			ss << "Line: " << line << '\n';
			ss << "Message: " << messageBuffer << '\n';

			std::cout << ss.str() << std::endl;
		}

	}
}
