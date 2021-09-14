#include <SDL.h>
#include "timer.hpp"

entityx::TimeDelta Timer::time() {
	return SDL_GetTicks() / 1000.0;
}