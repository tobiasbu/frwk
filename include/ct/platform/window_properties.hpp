
#ifndef _CHRONOTRIX_FRWK_WINDOW_PROPERTIES_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_PROPERTIES_HPP_

#include <ct/config/types.hpp>
#include <ct/platform/window_style.hpp>

namespace ct {

	////////////////////////////////////////////////////////////
	/// @brief Advanced Window properties creation options.
	///
	////////////////////////////////////////////////////////////
	struct CT_PLATFORM_API WindowProperties {
		u32 width;  ///< Window content's width
		u32 height; ///< Window content's height
		cstr title; ///< Window's title
		u32 style;  ///< Style of the window (see: ct::WindowStyle)

		////////////////////////////////////////////////////////////
		/// @brief Default constructor
		///
		////////////////////////////////////////////////////////////
		WindowProperties() = default;

		////////////////////////////////////////////////////////////
		/// @brief Construct a new Window Properties object
		///
		/// @param width Window width
		/// @param height Window height
		/// @param title Title
		/// @param style Style of window
		///
		/// @see ct::WindowStyle
		////////////////////////////////////////////////////////////
		WindowProperties(u32 width, u32 height, cstr title, u32 style = WindowStyle::Default);

		bool is_borderless() const;
		bool is_resizable() const;
		bool is_closable() const;
		bool has_title() const;
	};

} // namespace ct

#endif
