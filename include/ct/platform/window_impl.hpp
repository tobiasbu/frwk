
#ifndef _CHRONOTRIX_FRWK_WINDOW_IMPL_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_IMPL_HPP_

#include <ct/core/utils/noncopyable.hpp>
#include <ct/platform/window_handle.hpp>

namespace ct {

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

} // namespace ct

#endif
