
#include <purpur/purpur.hpp>
#include <purpur/platform/window.hpp>
#include <purpur/platform/window_style.hpp>

#include <chrono>
#include <thread>


using namespace ppr;

int main(int argc, char* argv[]) {

	Logger log = Logger();

	log.log("purpurina framework", PPR_FRWK_VERSION);

	Window win(480, 300, "teste");
    printf("is visible %d", win.isVisible());
	win.setVisible(true);

    bool isVisible = win.isVisible();
    bool current = isVisible;
    printf("is visible %d", current);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    win.setVisible(false);
    printf("is visible %d", win.isVisible());
    
	while (isVisible) {

		win.process();

        current = win.isVisible();
        if (current != isVisible) {
            isVisible = current;
            printf("is visible %d", current);
        }
	}

	return 0;
}
