#ifndef ENTITIES_FACTORY_HPP
#define ENTITIES_FACTORY_HPP

#include <entityx/entityx.h>
#include <box2d/box2d.h>
#include <SDL2/SDL.h>

enum Brick {
	One,
	Two,
	Three,
};

enum Wall {
	Top,
	Bottom,
	Left,
	Right,
};

class EntityFactory final {
public:
	EntityFactory(b2World *world, SDL_Renderer *renderer);
	void create_background(entityx::EntityManager &entities);
	void create_ball(entityx::EntityManager &entities);
	void create_brick(entityx::EntityManager &entities, Brick brick);
	void create_paddle(entityx::EntityManager &entities);
	void create_wall(entityx::EntityManager &entities, Wall wall);

private:
	b2World *world;
	SDL_Renderer *renderer;
};

#endif