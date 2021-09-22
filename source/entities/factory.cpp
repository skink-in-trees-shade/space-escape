#include "components/body.hpp"
#include "components/breakable.hpp"
#include "components/controlled.hpp"
#include "components/limited.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/size.hpp"
#include "core/config.hpp"
#include "factory.hpp"

EntityFactory::EntityFactory(b2World *world, SDL_Renderer *renderer) : world(world), renderer(renderer), floor(nullptr), paddle(nullptr) {
}

void EntityFactory::create_background(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();

	constexpr int x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT / 2, w = WINDOW_WIDTH, h = WINDOW_HEIGHT;

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Renderable>(Sprite::Background);
}

void EntityFactory::create_ball(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();

	constexpr int s = 4, x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT - 24, v = 160, vx = 64, vy = 64;

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

	body->SetLinearVelocity(b2Vec2(v / PTM_RATIO, v / PTM_RATIO));

	entity.assign<Size>(s, s);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
	entity.assign<Renderable>(Sprite::Ball);
	entity.assign<Limited>(v, vx, vy);
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
	Sprite sprite;
	bool breakable = true;
	switch (brick) {
	case Brick::One:
		sprite = Sprite::BrickOne;
		breakable = false;
		break;
	case Brick::Two:
		sprite = Sprite::BrickTwo;
		break;
	case Brick::Three:
		sprite = Sprite::BrickThree;
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

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
	entity.assign<Renderable>(sprite);
	if (breakable) {
		entity.assign<Breakable>();
	}
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

	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
	entity.assign<Renderable>(Sprite::Paddle);
	entity.assign<Controlled>();
}

void EntityFactory::create_wall(entityx::EntityManager &entities, Wall wall) {
	entityx::Entity entity = entities.create();

	constexpr int s = 6;
	int x, y, w, h;
	Sprite sprite;
	switch (wall) {
	case Wall::Top:
		x = WINDOW_WIDTH / 2;
		y = s / 2;
		w = WINDOW_WIDTH;
		h = s;
		sprite = Sprite::WallTop;
		break;
	case Wall::Bottom:
		x = WINDOW_WIDTH / 2;
		y = WINDOW_HEIGHT - s / 2;
		w = WINDOW_WIDTH;
		h = s;
		sprite = Sprite::WallBottom;
		break;
	case Wall::Left:
		x = s / 2;
		y = WINDOW_HEIGHT / 2;
		w = s;
		h = WINDOW_HEIGHT;
		sprite = Sprite::WallLeft;
		break;
	case Wall::Right:
		x = WINDOW_WIDTH - s / 2;
		y = WINDOW_HEIGHT / 2;
		w = s;
		h = WINDOW_HEIGHT;
		sprite = Sprite::WallRight;
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

	entity.assign<Renderable>(sprite);
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