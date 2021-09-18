#ifndef COMPONENTS_TEXTURE_HPP
#define COMPONENTS_TEXTURE_HPP

#include <SDL2/SDL.h>

struct Texture final {
	Texture(SDL_Texture *texture) : texture(texture) {}
	SDL_Texture *texture;
};

#endif