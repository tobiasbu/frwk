
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
		virtual bool is_visible() const = 0;
		virtual WindowHandle get_handle() const = 0;
		virtual void set_visible(bool visible) = 0;
	};

} // namespace ct

#endif
