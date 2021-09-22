#ifndef SYSTEMS_RENDER_HPP
#define SYSTEMS_RENDER_HPP

#include <map>
#include <entityx/entityx.h>
#include <SDL2/SDL.h>
#include "components/renderable.hpp"

class RenderSystem final : public entityx::System<RenderSystem> {
public:
	RenderSystem(SDL_Renderer *renderer);
	~RenderSystem();
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	SDL_Renderer *renderer;
	std::map<Sprite, SDL_Texture *> textures = {};
	SDL_Texture *get_texture(Sprite sprite);
};

#endif