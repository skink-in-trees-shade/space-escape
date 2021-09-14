#include "entities/ball.hpp"
#include "entities/wall.hpp"
#include "spawn.hpp"

SpawnSystem::SpawnSystem(World &world) : world(world), entities_spawned(false) {
}

void SpawnSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (!entities_spawned) {
		create_wall(entities, world.world, Wall::Top);
		create_wall(entities, world.world, Wall::Bottom);
		create_wall(entities, world.world, Wall::Left);
		create_wall(entities, world.world, Wall::Right);
		create_ball(entities, world.world);

		entities_spawned = true;
	}
}