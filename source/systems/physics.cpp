#include "components/body.hpp"
#include "components/position.hpp"
#include "physics.hpp"

PhysicsSystem::PhysicsSystem(World &world) : world(world) {
}

void PhysicsSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	world.world->Step(static_cast<float>(dt), 6, 2);

	entities.each<Body, Position>([this](entityx::Entity entity, Body &body, Position &position) {
		b2Vec2 pos = body.body->GetPosition();
		position.x = static_cast<int>(pos.x * PTM_RATIO);
		position.y = static_cast<int>(pos.y * PTM_RATIO);
	});
}