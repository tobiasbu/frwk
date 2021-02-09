
#ifndef _PURPURINA_FRWK_WINDOW_HPP_
#define _PURPURINA_FRWK_WINDOW_HPP_

#include <memory>

#include <purpur/core/types.hpp>
#include <purpur/core/utils/noncopyable.hpp>
#include <purpur/platform/export.hpp>
#include <purpur/platform/window_handle.hpp>
#include <purpur/platform/window_style.hpp>
#include <purpur/platform/window_properties.hpp>

namespace ppr {

	template<typename S>
	struct enable_make : public S
	{
		template<typename... T>
		enable_make(T&&... t)
			: S(std::forward<T>(t)...)
		{
		}
	};


	class WindowImpl;

	class PPR_PLATFORM_API Window : NonCopyable {

	protected:

		std::unique_ptr<WindowImpl> nativeWindow;
		Window(WindowImpl * nativeWindow);

	public:

		Window() = delete;
		virtual ~Window();

		WindowHandle getHandle() const;
		bool isVisible() const;
		void setVisible(bool visible);

		static std::unique_ptr<Window> create(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default);
		static std::unique_ptr<Window> create(const WindowProperties & properties);
	};



} // namespace ppr

#endif
