#include "components/position.hpp"
#include "components/size.hpp"
#include "components/texture.hpp"
#include "render.hpp"

RenderSystem::RenderSystem(SDL_Renderer *renderer) : renderer(renderer) {
}

void RenderSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	entities.each<Position, Size, Texture>([this](entityx::Entity entity, Position &position, Size &size, Texture &texture) {
		SDL_Rect rect = SDL_Rect();
		rect.x = position.x - size.w / 2;
		rect.y = position.y - size.h / 2;
		rect.w = size.w;
		rect.h = size.h;
		SDL_RenderCopy(renderer, texture.texture, nullptr, &rect);
	});

	SDL_RenderPresent(renderer);
}