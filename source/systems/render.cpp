#include <SDL.h>
#include "render.hpp"

RenderSystem::RenderSystem(Window &window) : window(window) {
}

void RenderSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	SDL_SetRenderDrawColor(window.renderer, 100, 140, 50, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(window.renderer);

	SDL_RenderPresent(window.renderer);
}