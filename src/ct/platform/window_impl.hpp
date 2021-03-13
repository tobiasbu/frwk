
#ifndef _CHRONOTRIX_FRWK_WINDOW_IMPL_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_IMPL_HPP_

#include <ct/core/utils/noncopyable.hpp>
#include <ct/platform/window_handle.hpp>
#include <ct/math/vec.hpp>

namespace ct {

	namespace internal {

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
			virtual vec2i get_position() const = 0;
			virtual WindowHandle get_handle() const = 0;
			virtual void set_position(const i32 & x, const i32 & y) = 0;
			virtual void set_position(const vec2i & position) = 0;
			virtual void set_visible(bool visible) = 0;
		};

	} // namespace internal

} // namespace ct

#endif
