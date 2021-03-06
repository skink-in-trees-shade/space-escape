#include "components/physics.hpp"
#include "components/position.hpp"
#include "core/config.hpp"
#include "physics.hpp"

PhysicsSystem::PhysicsSystem(b2World *world) : world(world) {
}

void PhysicsSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	world->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	entities.each<Physics, Position>([](entityx::Entity entity, Physics &physics, Position &position) {
		b2Vec2 pos = physics.body->GetPosition();
		position.x = pos.x * PTM_RATIO;
		position.y = pos.y * PTM_RATIO;
	});
}