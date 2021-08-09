
#ifndef _CHRONOTRIX_FRWK_WINDOW_IMPL_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_IMPL_HPP_

#include <ct/core/utils/noncopyable.hpp>
#include <ct/platform/window_handle.hpp>
#include <ct/math/vec.hpp>
#include <ct/math/rect.hpp>

namespace ct {

	namespace internal {

		////////////////////////////////////////////////////////////
		/// \brief Represents abstraction for OS-specifc window class
		///
		////////////////////////////////////////////////////////////
		class WindowImpl : NonCopyable {
		public:
			virtual ~WindowImpl() {};

			virtual bool is_visible() const = 0;
			virtual recti get_frame() const = 0;
			virtual recti get_content_frame() const = 0;
			virtual vec2i get_position() const = 0;
			virtual vec2u get_size() const = 0;
			virtual cstr get_title() const = 0;
			virtual WindowHandle get_handle() const = 0;

			virtual void set_frame(const recti & frame) = 0;
			virtual void set_position(const vec2i & position) = 0;
			virtual void set_size(const vec2u & size) = 0;
			virtual void set_title(cstr title) = 0;
			virtual void set_visible(bool visible) = 0;
		};

	} // namespace internal

} // namespace ct

#endif
