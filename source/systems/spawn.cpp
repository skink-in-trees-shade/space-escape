#include "entities/ball.hpp"
#include "entities/wall.hpp"
#include "spawn.hpp"

SpawnSystem::SpawnSystem(World &world, Window &window) : world(world), window(window), entities_spawned(false) {
}

void SpawnSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (!entities_spawned) {
		create_wall(entities, world.world, window.renderer, Wall::Top);
		create_wall(entities, world.world, window.renderer, Wall::Bottom);
		create_wall(entities, world.world, window.renderer, Wall::Left);
		create_wall(entities, world.world, window.renderer, Wall::Right);
		create_ball(entities, world.world, window.renderer);

		entities_spawned = true;
	}
}