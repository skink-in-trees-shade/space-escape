#ifndef ENTITIES_BRICK_HPP
#define ENTITIES_BRICK_HPP

#include <box2d/box2d.h>
#include <entityx/entityx.h>
#include <SDL2/SDL.h>

enum Brick {
	One,
	Two,
	Three,
};

void create_brick(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer, Brick brick);

#endif