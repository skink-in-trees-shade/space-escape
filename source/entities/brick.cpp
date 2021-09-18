#include <SDL2/SDL_image.h>
#include "components/body.hpp"
#include "components/position.hpp"
#include "components/size.hpp"
#include "components/texture.hpp"
#include "core/window.hpp"
#include "core/world.hpp"
#include "brick.hpp"

void create_brick(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer, Brick brick) {
	entityx::Entity entity = entities.create();

	constexpr int w = 10, h = 6;
	static int sx = 6 + w / 2, sy = h * 6;
	int x = sx, y = sy;
	sx += w;
	if (sx >= WINDOW_WIDTH - 6) {
		sx = 6 + w / 2;
		sy += h * 2;
	}
	const char *texname;
	switch (brick) {
	case Brick::One:
		texname = "assets/brick_1.png";
		break;
	case Brick::Two:
		texname = "assets/brick_2.png";
		break;
	case Brick::Three:
		texname = "assets/brick_3.png";
		break;
	}

	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&body_def);

	b2PolygonShape shape_def;
	shape_def.SetAsBox(w / 2 / PTM_RATIO, h / 2 / PTM_RATIO);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape_def;
	fixture_def.density = 10.0;
	fixture_def.friction = 0.0;
	fixture_def.restitution = 0.1f;
	b2Fixture *fixture = body->CreateFixture(&fixture_def);

	IMG_Init(IMG_INIT_PNG);
	SDL_Texture *texture = IMG_LoadTexture(renderer, texname);
	IMG_Quit();

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
	entity.assign<Texture>(texture);
}