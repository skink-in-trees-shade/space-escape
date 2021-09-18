#include <SDL2/SDL_image.h>
#include "components/body.hpp"
#include "components/position.hpp"
#include "components/size.hpp"
#include "components/texture.hpp"
#include "core/window.hpp"
#include "core/world.hpp"
#include "ball.hpp"

void create_ball(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer) {
	entityx::Entity entity = entities.create();

	constexpr int s = 4, x = (WINDOW_WIDTH - s) / 2, y = WINDOW_HEIGHT - 10 - s;

	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&body_def);

	b2CircleShape shape_def;
	shape_def.m_radius = s / 2.0 / PTM_RATIO;

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape_def;
	fixture_def.density = 1.0f;
	fixture_def.friction = 0.0f;
	fixture_def.restitution = 1.0f;
	b2Fixture *fixture = body->CreateFixture(&fixture_def);

	body->ApplyLinearImpulse(b2Vec2(0.05, 0.05), body_def.position, true);

	IMG_Init(IMG_INIT_PNG);

	SDL_Surface *surface = IMG_Load("assets/ball.png");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	IMG_Quit();

	entity.assign<Size>(s, s);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
	entity.assign<Texture>(texture);
}