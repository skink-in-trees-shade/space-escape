#include "components/body.hpp"
#include "components/position.hpp"
#include "components/size.hpp"
#include "core/world.hpp"
#include "ball.hpp"

void create_ball(entityx::EntityManager &entities, b2World *world) {
	entityx::Entity entity = entities.create();

	constexpr int x = 100, y = 100, s = 52;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x / PTM_RATIO, y / PTM_RATIO);
	b2Body *body = world->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = s / 2.0 / PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 1.0f;
	b2Fixture *fixture = body->CreateFixture(&fixtureDef);

	body->ApplyLinearImpulse(b2Vec2(10, 10), bodyDef.position, true);

	entity.assign<Size>(s, s);
	entity.assign<Position>(x, y);
	entity.assign<Body>(body);
}