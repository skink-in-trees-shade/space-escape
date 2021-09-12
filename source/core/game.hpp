#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <entityx/entityx.h>
#include "window.hpp"
#include "timer.hpp"

class Game final : private entityx::EntityX {
public:
	Game(Window &window, Timer &timer);
	void run();

private:
	Window &window;
	Timer &timer;
};

#endif