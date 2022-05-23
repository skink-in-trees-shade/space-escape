#ifndef CORE_RESOURCE_HPP
#define CORE_RESOURCE_HPP

#include <map>
#include <string>
#include <SDL2/SDL.h>

enum class Sprite {
	Background1,
	Background2,
	Ball,
	Brick,
	StrongBrick,
	Paddle,
	WallLeft,
	WallRight,
	WallTop,
	WallBottom,
	Font
};

class Resource final {
public:
	Resource(SDL_Renderer *renderer);
	~Resource();
	std::map<Sprite, SDL_Texture *> textures;
	std::map<int, std::string> levels;

private:
	SDL_Renderer *renderer;
};

#endif