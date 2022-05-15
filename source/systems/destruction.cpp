#include "components/physics.hpp"
#include "components/collided.hpp"
#include "destruction.hpp"

DestructionSystem::DestructionSystem(b2World *world) : world(world) {
}

void DestructionSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Physics, Collided>([&](entityx::Entity entity, Physics &physics, Collided &collided) {
		world->DestroyBody(physics.body);
		entity.destroy();
	});
}