
#ifndef _CHRONOTRIX_FRWK_PLATFORM_HPP_
#define _CHRONOTRIX_FRWK_PLATFORM_HPP_

#include <ct/platform/export.hpp>

namespace ct {

	/// Platform module
	namespace Platform {

		////////////////////////////////////////////////////////////
		/// @brief Initializes the platform internals Apis.
		///
		/// @return True if the initialization succeeds otherwise false
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API bool init();

		////////////////////////////////////////////////////////////
		/// @brief Terminates the platform internals Apis.
		///
		/// This will dispose any remaning window and will release
		/// allocated resources.
		///
		/// @return True if the termination succeeds otherwise false
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API bool terminate();

		////////////////////////////////////////////////////////////
		/// @brief Process window and input events.
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void poll_events();

	} // namespace Platform

} // namespace ct

#endif
