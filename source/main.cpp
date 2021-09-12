#include "core/window.hpp"
#include "core/timer.hpp"
#include "core/game.hpp"

int main() {
	Window window("Space Escape", 800, 600);
	Timer timer;
	Game game(window, timer);
	game.run();
}