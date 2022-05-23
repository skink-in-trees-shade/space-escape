#include "core/config.hpp"
#include "spawn.hpp"

SpawnSystem::SpawnSystem(EntityFactory *factory, Resource *resource, int round) : factory(factory), resource(resource), round(round) {
}

void SpawnSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (entities.size() == 0) {
		factory->create_background(entities, (round - 1) % 2);
		factory->create_top_wall(entities);
		factory->create_bottom_wall(entities);
		factory->create_left_wall(entities);
		factory->create_right_wall(entities);
		factory->create_ball(entities);
		factory->create_paddle(entities);

		std::string level = resource->levels[round];
		for (int y = 0; y < LEVEL_HEIGHT; y++) {
			for (int x = 0; x < LEVEL_WIDTH; x++) {
				switch (level[y * (LEVEL_WIDTH + 1) + x]) {
				case '1':
					factory->create_brick_one(entities, x, y);
					break;
				case '2':
					factory->create_brick_two(entities, x, y);
					break;
				case '3':
					factory->create_brick_three(entities, x, y);
					break;
				}
			}
		}

		factory->create_round_title_message(entities);
		factory->create_round_number_message(entities, round);

		factory->create_score_title_message(entities);
		factory->create_score_points_message(entities);
	}
}