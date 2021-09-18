#ifndef ENTITIES_BACKGROUND_HPP
#define ENTITIES_BACKGROUND_HPP

#include <box2d/box2d.h>
#include <entityx/entityx.h>
#include <SDL2/SDL.h>

void create_background(entityx::EntityManager &entities, b2World *world, SDL_Renderer *renderer);

#endif