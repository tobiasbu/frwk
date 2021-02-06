
#include <purpur/purpur.hpp>
#include <purpur/render/render_window.hpp>

#include <chrono>
#include <thread>


using namespace ppr;

int main(int argc, char* argv[]) {

	Logger log = Logger();

	log.log("purpurina frwk", PPR_FRWK_VERSION);

	RenderWidow * win = RenderWidow::create();
	win->setVisible(true);

    bool isVisible = win->isVisible();
	while (isVisible) {
		win->process();
	}

	return 0;
}
