#include "components/body.hpp"
#include "components/position.hpp"
#include "core/config.hpp"
#include "physics.hpp"

PhysicsSystem::PhysicsSystem(b2World *world) : world(world) {
}

void PhysicsSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	world->Step(dt, 6, 2);

	entities.each<Body, Position>([this](entityx::Entity entity, Body &body, Position &position) {
		b2Vec2 pos = body.body->GetPosition();
		position.x = pos.x * PTM_RATIO;
		position.y = pos.y * PTM_RATIO;
	});
}