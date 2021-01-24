
#include <purpur/purpur.hpp>
#include <purpur/platform/window.hpp>
#include <purpur/platform/window_style.hpp>

using namespace ppr;

int main(int argc, char* argv[]) {

	Logger log = Logger();

	log.log("hello");

	Window win = Window(480, 300, "teste", WindowStyle::Close | WindowStyle::Title | WindowStyle::Miniaturizable | WindowStyle::Resize);

	win.setVisible(true);

	while (win.isVisible()) {

		win.process();

	}

	return 0;
}
