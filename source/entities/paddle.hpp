#ifndef ENTITIES_PADDLE_HPP
#define ENTITIES_PADDLE_HPP

#include <box2d/box2d.h>
#include <entityx/entityx.h>
#include <SDL2/SDL.h>

void create_paddle(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer);

#endif