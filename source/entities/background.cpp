#include <SDL2/SDL_image.h>
#include "components/position.hpp"
#include "components/size.hpp"
#include "components/texture.hpp"
#include "core/window.hpp"
#include "background.hpp"

void create_background(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer) {
	entityx::Entity entity = entities.create();

	constexpr int x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT / 2, w = WINDOW_WIDTH, h = WINDOW_HEIGHT;

	IMG_Init(IMG_INIT_PNG);
	SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/background.png");
	IMG_Quit();

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Texture>(texture);
}