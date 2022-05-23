#ifndef SYSTEMS_RENDER_HPP
#define SYSTEMS_RENDER_HPP

#include <entityx/entityx.h>
#include <SDL2/SDL.h>
#include "core/resource.hpp"

class RenderSystem final : public entityx::System<RenderSystem> {
public:
	RenderSystem(SDL_Renderer *renderer, Resource *resource);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	SDL_Renderer *renderer;
	Resource *resource;
};

#endif