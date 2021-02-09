
#include <cstdarg> // va_start() and va_end()
#include <iostream>
#include <purpur/core/assert/assert_handler.hpp>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
namespace ppr {

	namespace internal {

		namespace Assert {

			namespace {
				constexpr uint32 PPR_ASSERT_BUFFER_SIZE = 1024;
				bool ignoreAll = false;
			}

			void ignoreAllAsserts(bool value) {
				ignoreAll = value;
			}

			bool ignoreAllAsserts() {
				return ignoreAll;
			}

			Action getAction(Level level, bool * ignore) {
				if (ignoreAll) {
					return Action::Ignore;
				}
				switch (level) {
					case Level::Error: return Action::Throw;
					case Level::Fatal: return Action::Abort;
					case Level::Debug: return Action::Break;
					case Level::Warning:
					default: return Action::Ignore;
				}
			}

			cstr handle(cstr file,
			            int32 line,
			            cstr function,
			            cstr expression,
			            bool * ignore,
			            cstr message,
			            ...) {
				char messageBuffer[PPR_ASSERT_BUFFER_SIZE] = {0};

				if (!!message) {
					va_list argptr;
					va_start(argptr, message);
					vsnprintf(messageBuffer, PPR_ASSERT_BUFFER_SIZE, message, argptr);
					va_end(argptr);
					message = messageBuffer;
				}

				std::stringstream ss;
				ss << "\nAssertion thrown!" << '\n';
				ss << "File: " << file << '\n';
				ss << "Line: " << line << '\n';

				if (!!function) {
					ss << "Function: " << function << '\n';
				}

				ss << "Expression: " << expression << '\n';
				if (!!message) {
					ss << "Message: " << messageBuffer << '\n';
				}

				std::cout << ss.str() << std::endl;

				return message;
			}
		} // namespace Assert
	}     // namespace internal
} // namespace ppr
