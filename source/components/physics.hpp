#ifndef COMPONENTS_PHYSICS_HPP
#define COMPONENTS_PHYSICS_HPP

#include <box2d/box2d.h>

struct Physics final {
	Physics(b2Body *body) : body(body) {}
	b2Body *body;
};

#endif