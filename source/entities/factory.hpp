#ifndef ENTITIES_FACTORY_HPP
#define ENTITIES_FACTORY_HPP

#include <entityx/entityx.h>

class EntityFactory final {
public:
	void create_background(entityx::EntityManager &entities, int n);
	void create_ball(entityx::EntityManager &entities);
	void create_brick_one(entityx::EntityManager &entities, int x, int y);
	void create_brick_two(entityx::EntityManager &entities, int x, int y);
	void create_brick_three(entityx::EntityManager &entities, int x, int y);
	void create_paddle(entityx::EntityManager &entities);
	void create_top_wall(entityx::EntityManager &entities);
	void create_bottom_wall(entityx::EntityManager &entities);
	void create_left_wall(entityx::EntityManager &entities);
	void create_right_wall(entityx::EntityManager &entities);
	void create_round_title_message(entityx::EntityManager &entities);
	void create_round_number_message(entityx::EntityManager &entities, int round);
	void create_score_title_message(entityx::EntityManager &entities);
	void create_score_points_message(entityx::EntityManager &entities);

private:
	void create_brick(entityx::EntityManager &entities, int x, int y, bool strong, int r, int g, int b, int points);
	void create_wall(entityx::EntityManager &entities, int x, int y, int w, int h);
};

#endif