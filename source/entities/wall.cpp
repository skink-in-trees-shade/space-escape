#include <SDL2/SDL_image.h>
#include "components/body.hpp"
#include "components/position.hpp"
#include "components/size.hpp"
#include "components/texture.hpp"
#include "core/window.hpp"
#include "core/world.hpp"
#include "wall.hpp"

void create_wall(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer, Wall wall) {
	entityx::Entity entity = entities.create();

	constexpr int s = 6;
	int x, y, w, h;
	const char *texname;
	switch (wall) {
	case Wall::Top:
		x = WINDOW_WIDTH / 2;
		y = s / 2;
		w = WINDOW_WIDTH;
		h = s;
		texname = "assets/wall_top.png";
		break;
	case Wall::Bottom:
		x = WINDOW_WIDTH / 2;
		y = WINDOW_HEIGHT - s / 2;
		w = WINDOW_WIDTH;
		h = s;
		texname = "assets/wall_bottom.png";
		break;
	case Wall::Left:
		x = s / 2;
		y = WINDOW_HEIGHT / 2;
		w = s;
		h = WINDOW_HEIGHT;
		texname = "assets/wall_left.png";
		break;
	case Wall::Right:
		x = WINDOW_WIDTH - s / 2;
		y = WINDOW_HEIGHT / 2;
		w = s;
		h = WINDOW_HEIGHT;
		texname = "assets/wall_right.png";
		break;
	}

	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&body_def);

	b2PolygonShape shape_def;
	shape_def.SetAsBox(w / PTM_RATIO / 2, h / PTM_RATIO / 2);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape_def;
	b2Fixture *fixture = body->CreateFixture(&fixture_def);

	IMG_Init(IMG_INIT_PNG);
	SDL_Texture *texture = IMG_LoadTexture(renderer, texname);
	IMG_Quit();
	entity.assign<Texture>(texture);

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
}