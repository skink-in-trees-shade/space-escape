#ifndef COMPONENTS_ANIMATION_HPP
#define COMPONENTS_ANIMATION_HPP

#include <vector>
#include <tuple>
#include "components/color.hpp"

struct Animation final {
	Animation(std::vector<std::tuple<int, Color>> frames, int total) : frames(frames), current(0), total(total) {}
	std::vector<std::tuple<int, Color>> frames;
	int current;
	int total;
};

#endif