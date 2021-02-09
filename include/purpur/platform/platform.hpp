
#ifndef _PURPURINA_FRWK_PLATFORM_HPP_
#define _PURPURINA_FRWK_PLATFORM_HPP_

#include <purpur/platform/export.hpp>

namespace ppr {

	namespace Platform {

		////////////////////////////////////////////////////////////
		/// @brief Initializes the platform internals Apis.
		///
		/// @return True if the initialization succeeds otherwise false
		///
		////////////////////////////////////////////////////////////
		PPR_PLATFORM_API bool init();

		////////////////////////////////////////////////////////////
		/// @brief Terminates the platform internals Apis.
		///
		/// This will dispose any remaning window and will release
		/// allocated resources.
		///
		/// @return True if the termination succeeds otherwise false
		///
		////////////////////////////////////////////////////////////
		PPR_PLATFORM_API bool terminate();

		////////////////////////////////////////////////////////////
		/// @brief Process window and input events.
		///
		////////////////////////////////////////////////////////////
		PPR_PLATFORM_API void poll_events();

	} // namespace Platform

} // namespace ppr

#endif
