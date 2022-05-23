#include <string>
#include <fstream>
#include <sstream>
#include <SDL2/SDL_image.h>
#include "core/config.hpp"
#include "resource.hpp"

Resource::Resource(SDL_Renderer *renderer) : renderer(renderer) {
	const static std::map<Sprite, std::string> asset_map = {
		{Sprite::Background1, "background_1"},
		{Sprite::Background2, "background_2"},
		{Sprite::Ball, "ball"},
		{Sprite::Brick, "brick"},
		{Sprite::StrongBrick, "strong_brick"},
		{Sprite::Paddle, "paddle"},
		{Sprite::WallLeft, "wall_left"},
		{Sprite::WallRight, "wall_right"},
		{Sprite::WallTop, "wall_top"},
		{Sprite::WallBottom, "wall_bottom"},
		{Sprite::Font, "font"},
	};
	IMG_Init(IMG_INIT_PNG);
	for (const auto &asset : asset_map) {
		textures[asset.first] = IMG_LoadTexture(renderer, ("assets/images/" + asset.second + ".png").c_str());
	}
	IMG_Quit();

	const static std::map<int, std::string> level_map = {
		{1, "01"},
		{2, "02"},
	};
	for (const auto &level : level_map) {
		std::ifstream file("assets/levels/level" + level.second + ".dat");
		std::stringstream buffer;
		buffer << file.rdbuf();
		levels[level.first] = buffer.str().c_str();
	}
}

Resource::~Resource() {
	for (const auto &texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
}