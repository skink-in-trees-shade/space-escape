#include <SDL2/SDL_image.h>
#include "components/body.hpp"
#include "components/controlled.hpp"
#include "components/position.hpp"
#include "components/size.hpp"
#include "components/texture.hpp"
#include "core/config.hpp"
#include "factory.hpp"

EntityFactory::EntityFactory(b2World *world, SDL_Renderer *renderer) : world(world), renderer(renderer), floor(nullptr), paddle(nullptr) {
}

void EntityFactory::create_background(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();

	constexpr int x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT / 2, w = WINDOW_WIDTH, h = WINDOW_HEIGHT;

	SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/background.png");

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Texture>(texture);
}

void EntityFactory::create_ball(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();

	constexpr int s = 4, x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT - 24;

	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.fixedRotation = true;
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
	SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/ball.png");
	IMG_Quit();

	entity.assign<Size>(s, s);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
	entity.assign<Texture>(texture);
}

void EntityFactory::create_brick(entityx::EntityManager &entities, Brick brick) {
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
	body_def.fixedRotation = true;
	body_def.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&body_def);

	b2PolygonShape shape_def;
	shape_def.SetAsBox(w / 2.0 / PTM_RATIO, h / 2.0 / PTM_RATIO);

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

void EntityFactory::create_paddle(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();

	constexpr int w = 20, h = 6, x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT - 12;

	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.fixedRotation = true;
	body_def.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&body_def);

	paddle = body;
	create_paddle_joint();

	b2PolygonShape shape_def;
	shape_def.SetAsBox(w / 2.0 / PTM_RATIO, h / 2.0 / PTM_RATIO);

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
	entity.assign<Controlled>();
}

void EntityFactory::create_wall(entityx::EntityManager &entities, Wall wall) {
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
	body_def.fixedRotation = true;
	body_def.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&body_def);

	if (wall == Wall::Bottom) {
		floor = body;
		create_paddle_joint();
	}

	b2PolygonShape shape_def;
	shape_def.SetAsBox(w / 2.0 / PTM_RATIO, h / 2.0 / PTM_RATIO);

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

void EntityFactory::create_paddle_joint() {
	if (floor != nullptr && paddle != nullptr) {
		b2PrismaticJointDef jointDef;
		jointDef.collideConnected = true;
		jointDef.Initialize(paddle, floor, paddle->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
		world->CreateJoint(&jointDef);
	}
}