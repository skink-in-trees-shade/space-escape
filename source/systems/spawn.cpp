#include "entities/background.hpp"
#include "entities/ball.hpp"
#include "entities/brick.hpp"
#include "entities/paddle.hpp"
#include "entities/wall.hpp"
#include "spawn.hpp"

SpawnSystem::SpawnSystem(World &world, Window &window) : world(world), window(window), entities_spawned(false) {
}

void SpawnSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (!entities_spawned) {
		const int bricks_per_line = 10;
		create_background(entities, world.world, window.renderer);
		create_wall(entities, world.world, window.renderer, Wall::Top);
		create_wall(entities, world.world, window.renderer, Wall::Bottom);
		create_wall(entities, world.world, window.renderer, Wall::Left);
		create_wall(entities, world.world, window.renderer, Wall::Right);
		create_ball(entities, world.world, window.renderer);
		create_paddle(entities, world.world, window.renderer);
		for (int i = 0; i < bricks_per_line; i++) {
			create_brick(entities, world.world, window.renderer, Brick::One);
		}
		for (int i = 0; i < bricks_per_line; i++) {
			create_brick(entities, world.world, window.renderer, Brick::Two);
		}
		for (int i = 0; i < bricks_per_line; i++) {
			create_brick(entities, world.world, window.renderer, Brick::Three);
		}

		entities_spawned = true;
	}
}