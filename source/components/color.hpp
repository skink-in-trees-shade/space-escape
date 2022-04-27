#ifndef COMPONENTS_COLOR_HPP
#define COMPONENTS_COLOR_HPP

struct Color final {
	Color(int r, int g, int b) : r(r), g(g), b(b) {}
	int r;
	int g;
	int b;
};

#endif