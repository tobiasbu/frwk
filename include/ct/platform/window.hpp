
#ifndef _CHRONOTRIX_FRWK_WINDOW_HPP_
#define _CHRONOTRIX_FRWK_WINDOW_HPP_

#include <memory>

#include <ct/core/types.hpp>
#include <ct/core/utils/noncopyable.hpp>
#include <ct/core/utils/type_traits.hpp>
#include <ct/platform/export.hpp>
#include <ct/platform/window_handle.hpp>
#include <ct/platform/window_style.hpp>
#include <ct/platform/window_properties.hpp>

namespace ct {

	class WindowImpl;
	class Window;
	using WindowPtr = std::unique_ptr<Window>;


	template<typename S>
	struct enable_make : public S
	{
		template<typename... T>
		enable_make(T&&... t)
			: S(FWD(t)...)
		{
		}
	};

	namespace create {
		CT_PLATFORM_API WindowPtr window(const WindowProperties & properties);
		CT_PLATFORM_API WindowPtr window(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default);
	}


	class CT_PLATFORM_API Window : NonCopyable {

	using WindowImplPtr = std::unique_ptr<WindowImpl>;

	friend WindowPtr create::window(const WindowProperties & properties);
	friend WindowPtr create::window(uint32 width, uint32 height, cstr title, uint32 style);

	protected:

		WindowImplPtr impl;
		Window(WindowImpl * impl);

	public:

		Window() = delete;
		virtual ~Window();

		WindowHandle getHandle() const;
		bool isVisible() const;
		void setVisible(bool visible);

		void close();

	};





} // namespace ct

#endif
