
#ifndef _CHRONOTRIX_FRWK_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_HPP_

#include <ct/config/types.hpp>
#include <ct/core/utils/noncopyable.hpp>
#include <ct/core/types/type_traits.hpp>
#include <ct/math/rect.hpp>
#include <ct/math/vec.hpp>
#include <ct/platform/export.hpp>
#include <ct/platform/window_handle.hpp>
#include <ct/platform/window_properties.hpp>
#include <ct/platform/window_style.hpp>
#include <memory>

namespace ct {

	namespace internal {
		class WindowImpl;
	}

	class Window;
	using WindowPtr = std::unique_ptr<Window>;

	////////////////////////////////////////////////////////////
	/// @brief Workaround to enable to make smart pointers
	/// from private or protected ctor.
	///
	/// @tparam S Instance to enable make an pointer from.
	///
	/// @see https://stackoverflow.com/a/8147326
	////////////////////////////////////////////////////////////
	template <typename S>
	struct enable_make : public S {
		////////////////////////////////////////////////////////////
		/// @brief Constructs a instance S by forwarding ctor arguments
		///
		/// @tparam T ctor arguments
		/// @param t Arguments
		////////////////////////////////////////////////////////////
		template <typename... T>
		enable_make(T &&... t) : S(FWD(t)...) {}
	};

	////////////////////////////////////////////////////////////
	/// @brief Represents window instance
	///
	////////////////////////////////////////////////////////////
	class Window : NonCopyable {
		friend CT_PLATFORM_API WindowPtr create_window(const WindowProperties & properties);
		friend CT_PLATFORM_API WindowPtr create_window(u32 width, u32 height, cstr title, u32 style);

	private:
		internal::WindowImpl * impl; ///< Window implementation

	protected:
		////////////////////////////////////////////////////////////
		/// @brief Constructs a window instance
		///
		/// @param impl Internal window implementation
		///
		////////////////////////////////////////////////////////////
		Window(internal::WindowImpl * impl);

	public:
		////////////////////////////////////////////////////////////
		/// @brief Non-constructible
		/// To create an window please use create_window factory method.
		///
		////////////////////////////////////////////////////////////
		Window() = delete;

		////////////////////////////////////////////////////////////
		/// @brief Move constructor
		///
		/// @param other Window
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API explicit Window(Window && other);

		////////////////////////////////////////////////////////////
		/// @brief Destroy the Window instance
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API virtual ~Window();

		////////////////////////////////////////////////////////////
		/// @brief Get the native window handle
		///
		/// @return WindowHandle
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API WindowHandle get_handle() const;

		////////////////////////////////////////////////////////////
		/// @brief Get window's content size in pixels
		///
		/// Does not include title bar size or offset attributes.
		/// It only considered the inner frame size of the window.
		///
		/// @return Size of the window content
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API vec2u get_content_size() const;

		////////////////////////////////////////////////////////////
		/// @brief Get window's frame rectangle in screen coordinates
		///
		/// The dimensions of window frame includes title bar and
		/// any other offset attribute (like shadow radius).
		///
		/// @return Window's frame
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API recti get_frame() const;

		////////////////////////////////////////////////////////////
		/// @brief Get window's position in pixels
		///
		/// The position are relative to the upper-left
		/// corner of the screen.
		///
		/// @return Position of the window
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API vec2i get_position() const;

		////////////////////////////////////////////////////////////
		/// @brief Get window's size in pixels
		///
		/// @return Size of the window
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API vec2u get_size() const;

		////////////////////////////////////////////////////////////
		/// @brief Get window title
		///
		/// @return Window title name
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API cstr get_title() const;

		////////////////////////////////////////////////////////////
		/// @brief Check if window is visible the in screen
		///
		/// @return True is visible to the user otherwise false
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API bool is_visible() const;

		CT_PLATFORM_API bool is_open() const;

		////////////////////////////////////////////////////////////
		/// @brief Set the window's content size
		///
		/// Does not include title bar size or offset attributes.
		/// It only considered the inner frame size of the window.
		///
		/// @param size Content size
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_content_size(const vec2u & content_size);

		////////////////////////////////////////////////////////////
		/// @brief Set position and size of the window frame
		///
		/// @param frame Window's frame
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_frame(const recti & frame);

		////////////////////////////////////////////////////////////
		/// @brief Set the window position
		///
		/// @param position New position of the window
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_position(const vec2i & position);

		////////////////////////////////////////////////////////////
		/// @brief Set the window position
		///
		/// @param x Horizontal screen coordinate
		/// @param y Vertical screen coordinate
		//
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_position(const i32 & x, const i32 & y);

		////////////////////////////////////////////////////////////
		/// @brief Set the window size
		///
		/// @param x Window width
		/// @param y Window height
		//
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_size(const vec2u & size);

		////////////////////////////////////////////////////////////
		/// @brief Set window visibility
		///
		/// @param visible Visibility flag
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_visible(bool visible);

		////////////////////////////////////////////////////////////
		/// @brief Set the window title
		///
		/// @param UTF8 encoded window title
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_title(cstr title);

		////////////////////////////////////////////////////////////
		/// @brief Closes the window and release internal pointers
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void close();

	protected:
		static CT_PLATFORM_API internal::WindowImpl * create_window_impl(const WindowProperties & properties);
	};

	CT_PLATFORM_API WindowPtr create_window(const WindowProperties & properties);
	CT_PLATFORM_API WindowPtr create_window(u32 width, u32 height, cstr title, u32 style = WindowStyle::Default);

} // namespace ct

#endif
