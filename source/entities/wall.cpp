#include "core/window.hpp"
#include "core/world.hpp"
#include "wall.hpp"

void create_wall(entityx::EntityManager &entities, b2World *world, Wall wall) {
	entityx::Entity entity = entities.create();

	b2BodyDef bodyDef;
	bodyDef.position.SetZero();
	b2Body *body = world->CreateBody(&bodyDef);

	b2EdgeShape shape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	switch (wall) {
	case Wall::Top:
		shape.SetTwoSided(b2Vec2(0, 0), b2Vec2(WINDOW_WIDTH / PTM_RATIO, 0));
		break;
	case Wall::Bottom:
		shape.SetTwoSided(b2Vec2(0, WINDOW_HEIGHT / PTM_RATIO), b2Vec2(WINDOW_WIDTH / PTM_RATIO, WINDOW_HEIGHT / PTM_RATIO));
		break;
	case Wall::Left:
		shape.SetTwoSided(b2Vec2(0, 0), b2Vec2(0, WINDOW_HEIGHT / PTM_RATIO));
		break;
	case Wall::Right:
		shape.SetTwoSided(b2Vec2(WINDOW_WIDTH / PTM_RATIO, WINDOW_HEIGHT / PTM_RATIO), b2Vec2(WINDOW_WIDTH / PTM_RATIO, 0));
		break;
	}
	b2Fixture *fixture = body->CreateFixture(&fixtureDef);
}