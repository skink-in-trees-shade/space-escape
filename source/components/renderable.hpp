#ifndef COMPONENTS_RENDERABLE_HPP
#define COMPONENTS_RENDERABLE_HPP

#include "core/resource.hpp"

struct Renderable final {
	Renderable(Sprite sprite) : sprite(sprite) {}
	Sprite sprite;
};

#endif