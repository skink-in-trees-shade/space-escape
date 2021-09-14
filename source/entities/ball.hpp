#ifndef ENTITIES_BALL_HPP
#define ENTITIES_BALL_HPP

#include <box2d/box2d.h>
#include <entityx/entityx.h>

void create_ball(entityx::EntityManager &entities, b2World *world);

#endif