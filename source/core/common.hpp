#ifndef CORE_COMMON_HPP
#define CORE_COMMON_HPP

#include <SDL2/SDL.h>
#include <box2d/box2d.h>

class Common final {
public:
	Common();
	~Common();
	SDL_Window *window;
	SDL_Renderer *renderer;
	b2World *world;
};

#endif