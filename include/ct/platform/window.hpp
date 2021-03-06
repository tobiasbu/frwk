
#ifndef _CHRONOTRIX_FRWK_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_HPP_

#include <ct/config/types.hpp>
#include <ct/core/utils/noncopyable.hpp>
#include <ct/core/utils/type_traits.hpp>
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
		using WindowImplPtr = std::unique_ptr<internal::WindowImpl>;

		friend CT_PLATFORM_API WindowPtr create_window(const WindowProperties & properties);
		friend CT_PLATFORM_API WindowPtr create_window(u32 width,
		                                               u32 height,
		                                               cstr title,
		                                               u32 style);

	protected:
		WindowImplPtr impl; ///< Window implementation

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
		/// @brief Check if window is visible the in screen
		///
		/// @return True is visible to the user otherwise false
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API bool is_visible() const;

		////////////////////////////////////////////////////////////
		/// @brief Set window visibility
		///
		/// @param visible
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void set_visible(bool visible);

		////////////////////////////////////////////////////////////
		/// @brief Closes the window and release internal pointers
		///
		////////////////////////////////////////////////////////////
		CT_PLATFORM_API void close();

	protected:
		static CT_PLATFORM_API internal::WindowImpl *
		create_window_impl(const WindowProperties & properties);
	};

	CT_PLATFORM_API WindowPtr create_window(const WindowProperties & properties);
	CT_PLATFORM_API WindowPtr create_window(u32 width,
	                                        u32 height,
	                                        cstr title,
	                                        u32 style = WindowStyle::Default);

} // namespace ct

#endif
