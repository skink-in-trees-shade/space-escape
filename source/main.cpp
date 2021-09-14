#include "core/game.hpp"
#include "core/timer.hpp"
#include "core/window.hpp"
#include "core/world.hpp"

int main() {
	Window window;
	World world;
	Timer timer;
	Game game(window, world, timer);
	game.run();
}