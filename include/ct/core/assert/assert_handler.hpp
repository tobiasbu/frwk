////////////////////////////////////////////////////////////
// Chronotrix Framework
//
// \todo Copyright notice
//
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_DEBUG_ASSERT_HANDLER_HPP_
#define _CHRONOTRIX_FRWK_DEBUG_ASSERT_HANDLER_HPP_

#include <ct/config/types.hpp>
#include <ct/core/export.hpp>

namespace ct {
	namespace internal {
		namespace Assert {

			enum class Action
			{
				None,
				Ignore,
				Break,
				Throw,
				Abort,
			};

			enum class Level
			{
				Warning = 8,
				Debug = 16,
				Error = 32,
				Fatal = 64
			};

			CT_CORE_API Action get_action(Level level = Level::Error, bool ignore = false);

			CT_CORE_API cstr handle(cstr file,
			                        i32 line,
			                        cstr function,
			                        cstr expression,
			                        bool ignore,
			                        cstr message,
			                        ...);

			CT_CORE_API bool ignore_all_asserts();
		} // namespace Assert

	} // namespace internal

} // namespace ct

#endif
