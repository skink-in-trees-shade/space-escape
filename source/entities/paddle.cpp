#include <SDL2/SDL_image.h>
#include "components/body.hpp"
#include "components/position.hpp"
#include "components/size.hpp"
#include "components/texture.hpp"
#include "core/window.hpp"
#include "core/world.hpp"
#include "paddle.hpp"

void create_paddle(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer) {
	entityx::Entity entity = entities.create();

	constexpr int w = 20, h = 6, x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT - 12;

	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&body_def);

	b2PolygonShape shape_def;
	shape_def.SetAsBox(w / 2 / PTM_RATIO, h / 2 / PTM_RATIO);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape_def;
	fixture_def.density = 10.0f;
	fixture_def.friction = 0.4f;
	fixture_def.restitution = 0.1f;
	b2Fixture *fixture = body->CreateFixture(&fixture_def);

	IMG_Init(IMG_INIT_PNG);
	SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/paddle.png");
	IMG_Quit();

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
	entity.assign<Texture>(texture);
}