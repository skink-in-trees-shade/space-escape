#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <entityx/entityx.h>
#include "timer.hpp"
#include "window.hpp"
#include "world.hpp"

class Game final : private entityx::EntityX {
public:
	Game(Window &window, World &world, Timer &timer);
	void run();

private:
	Window &window;
	World &world;
	Timer &timer;
};

#endif