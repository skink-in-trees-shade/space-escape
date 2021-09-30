#include <SDL2/SDL_image.h>
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/size.hpp"
#include "render.hpp"

RenderSystem::RenderSystem(SDL_Renderer *renderer) : renderer(renderer) {
}

RenderSystem::~RenderSystem() {
	for (const std::pair<Sprite, SDL_Texture *> &texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
}

void RenderSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	entities.each<Position, Size, Renderable>([this](entityx::Entity entity, Position &position, Size &size, Renderable &renderable) {
		SDL_Rect rect = SDL_Rect();
		rect.x = position.x - size.w / 2;
		rect.y = position.y - size.h / 2;
		rect.w = size.w;
		rect.h = size.h;
		SDL_RenderCopy(renderer, get_texture(renderable.sprite), nullptr, &rect);
	});

	SDL_RenderPresent(renderer);
}

SDL_Texture *RenderSystem::get_texture(Sprite sprite) {
	std::map<Sprite, SDL_Texture *>::iterator iterator = textures.find(sprite);
	if (iterator != textures.end()) {
		return iterator->second;
	}
	static std::map<Sprite, const char *> assets = {
		{Sprite::Background, "assets/background.png"},
		{Sprite::Ball, "assets/ball.png"},
		{Sprite::BrickOne, "assets/brick_1.png"},
		{Sprite::BrickTwo, "assets/brick_2.png"},
		{Sprite::BrickThree, "assets/brick_3.png"},
		{Sprite::Paddle, "assets/paddle.png"},
		{Sprite::WallLeft, "assets/wall_left.png"},
		{Sprite::WallRight, "assets/wall_right.png"},
		{Sprite::WallTop, "assets/wall_top.png"},
		{Sprite::WallBottom, "assets/wall_bottom.png"},
	};
	return textures[sprite] = IMG_LoadTexture(renderer, assets[sprite]);
}