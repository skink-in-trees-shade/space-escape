#ifndef COMPONENTS_POSITION_HPP
#define COMPONENTS_POSITION_HPP

struct Position final {
	Position(int x, int y) : x(x), y(y) {}
	int x;
	int y;
};

#endif