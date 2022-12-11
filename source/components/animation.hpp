#ifndef COMPONENTS_ANIMATION_HPP
#define COMPONENTS_ANIMATION_HPP

#include <vector>
#include "components/color.hpp"

struct Animation final {
	Animation(std::vector<Color> frames) : frames(frames), current(0) {}
	std::vector<Color> frames;
	int current;
};

#endif