#ifndef ENTITIES_WALL_HPP
#define ENTITIES_WALL_HPP

#include <box2d/box2d.h>
#include <entityx/entityx.h>

enum Wall {
	Top,
	Bottom,
	Left,
	Right
};

void create_wall(entityx::EntityManager &entities, b2World *world, Wall wall);

#endif