
#ifndef _PURPURINA_FRWK_WINDOW_HPP_
#define _PURPURINA_FRWK_WINDOW_HPP_

#include <purpur/core/types.hpp>
#include <purpur/core/utils/noncopyable.hpp>
#include <purpur/platform/export.hpp>
#include <purpur/platform/window_handle.hpp>
#include <purpur/platform/window_style.hpp>

namespace ppr {


	class NativeWindow;

	class PPR_PLATFORM_API Window : public NonCopyable {
	protected:
		NativeWindow * nativeWindow;

	public:
		Window(NativeWindow * nativeWindow);
		Window(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default);
		~Window();

		bool isVisible();
		void setVisible(bool visible);
		void process();
		WindowHandle getHandle();

		static void create(uint32 width, uint32 height, cstr title, uint32 style = WindowStyle::Default);
	};

} // namespace ppr

#endif
