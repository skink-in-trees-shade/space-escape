#ifndef COMPONENTS_BODY_HPP
#define COMPONENTS_BODY_HPP

#include <box2d/box2d.h>

struct Body final {
	Body(b2Body *body) : body(body) {}
	b2Body *body;
};

#endif