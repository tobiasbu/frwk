
#include <ct/ct.hpp>

#include <ct/platform/platform.hpp>
#include <ct/platform/window.hpp>


int main(int argc, char * argv[]) {
	ct::Logger logger;

	logger.log("chronotrix frwk", CT_FRWK_VERSION);

	if (!ct::Platform::init()) {
		logger.log("Could not initialize Platform");
		return 1;
	}
	
	logger.log("Opening window");

	ct::Window win;
	win.create(480, 360, "Chronotrix Simple Window");  

	while (win.is_open()) {
	 	ct::Platform::poll_events();
	}

	logger.log("Terminating");
	if (!ct::Platform::terminate()) {
		return 1;
	}

	return 0;
}
