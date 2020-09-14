
#include <purpurina/Config.hpp>

#ifdef PURPURINA_OS_WINDOWS
	#include <windows.h>
#endif

namespace ppr {

	struct Vector2i {
		int32 x;
		int32 y;
	};

	class Window {

	public:

		Window();

		static void create(Vector2i size, const char * title) {

			uint32      PixelFormat;            // Holds The Results After Searching For A Match
			WNDCLASS    wc;                     // Windows Class Structure
			DWORD       dwExStyle;              // Window Extended Style
			DWORD       dwStyle;                // Window Style
			RECT        WindowRect;             // Grabs Rectangle Upper Left / Lower Right Values
			WindowRect.left=(long)0;            // Set Left Value To 0
			WindowRect.right=(long)size.x;      // Set Right Value To Requested Width
			WindowRect.top=(long)0;             // Set Top Value To 0
			WindowRect.bottom=(long)size.y;     // Set Bottom Value To Requested Height

		}
	};
}
