#include "spawn.hpp"

SpawnSystem::SpawnSystem(EntityFactory *factory) : factory(factory) {
}

void SpawnSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (!entities_spawned) {
		factory->create_background(entities);
		factory->create_wall(entities, Wall::Top);
		factory->create_wall(entities, Wall::Bottom);
		factory->create_wall(entities, Wall::Left);
		factory->create_wall(entities, Wall::Right);
		factory->create_ball(entities);
		factory->create_paddle(entities);
		constexpr int bricks_per_line = 10;
		for (int i = 0; i < bricks_per_line; i++) {
			factory->create_brick(entities, Brick::One);
		}
		for (int i = 0; i < bricks_per_line; i++) {
			factory->create_brick(entities, Brick::Two);
		}
		for (int i = 0; i < bricks_per_line; i++) {
			factory->create_brick(entities, Brick::Three);
		}
		entities_spawned = true;
	}
}