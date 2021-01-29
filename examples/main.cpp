
#include <purpur/purpur.hpp>
#include <purpur/platform/window.hpp>
#include <purpur/platform/window_style.hpp>

using namespace ppr;

int main(int argc, char* argv[]) {

	Logger log = Logger();

	log.log("purpurina framework", PPR_FRWK_VERSION);

	Window win(480, 300, "teste", WindowStyle::make(false, true, true, true, false));
	win.setVisible(true);

	while (win.isVisible()) {

		win.process();

	}

	return 0;
}
