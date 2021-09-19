#ifndef SYSTEM_RENDER_HPP
#define SYSTEM_RENDER_HPP

#include <entityx/entityx.h>
#include <SDL2/SDL.h>

class RenderSystem final : public entityx::System<RenderSystem> {
public:
	RenderSystem(SDL_Renderer *renderer);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	SDL_Renderer *renderer;
};

#endif