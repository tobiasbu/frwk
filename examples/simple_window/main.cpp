
#include <purpur/purpur.hpp>

#include <purpur/platform/platform.hpp>
#include <purpur/platform/window.hpp>

using namespace ppr;

int main(int argc, char* argv[]) {

	Logger logger = Logger();

	logger.log("purpurina frwk", PPR_FRWK_VERSION);


	if (!Platform::init()) {
		logger.log("Could not initialize Platform");
		return 1;
	}

	logger.log("Opening window");

	auto win = create::window(480, 300, "test");
	win->setVisible(true);

	while (win->isVisible()) {
	 	Platform::poll_events();
	}

	logger.log("Terminating");
	if (!Platform::terminate()) {
		return 1;
	}

	return 0;
}
