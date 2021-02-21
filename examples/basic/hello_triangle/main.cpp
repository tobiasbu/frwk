
#include <ct/ct.hpp>
#include <ct/platform/platform.hpp>
#include <ct/render/render.hpp>
#include <ct/render/render_window.hpp>

using namespace ct;

int main(int argc, char const *argv[])
{
	Logger logger = Logger();

	if (!Platform::init()) {
		logger.log("Could not initialize Platform module");
		return 1;
	}

	if (!Render::init()) {
		logger.log("Could not initialize Render module");
		return 1;
	}

	logger.log("Opening window...");

	auto win = create_render_window(480, 300, "teste");
	win->set_visible(true);

	while (win->is_visible()) {
		Platform::poll_events();
	}

	if (!Render::terminate()) {
		logger.log("Could not initialize Render module");
		return 1;
	}


	if (!Platform::terminate()) {
		logger.log("Terminating with error.");
		return 1;
	}

	return 0;
}
