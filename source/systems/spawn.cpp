#include <fstream>
#include "core/config.hpp"
#include "spawn.hpp"

SpawnSystem::SpawnSystem(EntityFactory *factory, int round) : factory(factory), round(round) {
}

void SpawnSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (entities.size() == 0) {
		factory->create_background(entities);
		factory->create_wall(entities, Wall::Top);
		factory->create_wall(entities, Wall::Bottom);
		factory->create_wall(entities, Wall::Left);
		factory->create_wall(entities, Wall::Right);
		factory->create_ball(entities);
		factory->create_paddle(entities);

		std::ifstream level("assets/levels/level" + ((round < 10 ? "0" : "") + std::to_string(round)) + ".dat");
		for (int y = 0; y < LEVEL_HEIGHT; y++) {
			std::string row;
			std::getline(level, row);
			for (int x = 0; x < LEVEL_WIDTH; x++) {
				switch (row[x]) {
				case '1':
					factory->create_brick(entities, Brick::One, x, y);
					break;
				case '2':
					factory->create_brick(entities, Brick::Two, x, y);
					break;
				case '3':
					factory->create_brick(entities, Brick::Three, x, y);
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