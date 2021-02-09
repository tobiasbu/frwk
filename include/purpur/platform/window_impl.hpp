
#ifndef _PURPURINA_FRWK_WINDOW_IMPL_HPP_
#define _PURPURINA_FRWK_WINDOW_IMPL_HPP_

#include <purpur/core/utils/noncopyable.hpp>
#include <purpur/platform/window_handle.hpp>

namespace ppr {

	////////////////////////////////////////////////////////////
	/// \brief Represents abstraction for OS-specifc window class
	///
	////////////////////////////////////////////////////////////
	class WindowImpl : NonCopyable {
	public:
		virtual ~WindowImpl() {};

		////////////////////////////////////////////////////////////
		/// @brief Tell whether or not the window is visible onscreen
		///
		/// @return True if the window is visible otherwise false
		///
		////////////////////////////////////////////////////////////
		virtual bool isVisible() const = 0;
		virtual WindowHandle getHandle() const = 0;
		virtual void setVisible(bool visible) = 0;
	};

} // namespace ppr

#endif
