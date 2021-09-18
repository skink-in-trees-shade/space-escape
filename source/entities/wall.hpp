#ifndef ENTITIES_WALL_HPP
#define ENTITIES_WALL_HPP

#include <box2d/box2d.h>
#include <entityx/entityx.h>
#include <SDL2/SDL.h>

enum Wall {
	Top,
	Bottom,
	Left,
	Right,
};

void create_wall(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer, Wall wall);

#endif