#ifndef ENTITIES_BALL_HPP
#define ENTITIES_BALL_HPP

#include <box2d/box2d.h>
#include <entityx/entityx.h>
#include <SDL2/SDL.h>

void create_ball(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer);

#endif