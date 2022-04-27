#ifndef ENTITIES_FACTORY_HPP
#define ENTITIES_FACTORY_HPP

#include <entityx/entityx.h>

enum class Brick {
	One,
	Two,
	Three,
};

enum class Wall {
	Top,
	Bottom,
	Left,
	Right,
};

class EntityFactory final {
public:
	void create_background(entityx::EntityManager &entities);
	void create_ball(entityx::EntityManager &entities);
	void create_brick(entityx::EntityManager &entities, Brick brick);
	void create_paddle(entityx::EntityManager &entities);
	void create_wall(entityx::EntityManager &entities, Wall wall);
	void create_round_title_message(entityx::EntityManager &entities);
	void create_round_number_message(entityx::EntityManager &entities, int round);
};

#endif