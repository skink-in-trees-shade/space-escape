#include "components/position.hpp"
#include "components/size.hpp"
#include "render.hpp"

RenderSystem::RenderSystem(Window &window) : window(window) {
}

void RenderSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	SDL_SetRenderDrawColor(window.renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(window.renderer);

	entities.each<Position, Size>([this](entityx::Entity entity, Position &position, Size &size) {
		SDL_Rect rect = {.x = position.x - size.w / 2, .y = position.y - size.h / 2, .w = size.w, .h = size.h};
		SDL_SetRenderDrawColor(window.renderer, 234, 177, 147, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(window.renderer, &rect);
	});

	SDL_RenderPresent(window.renderer);
}