#ifndef COMPONENTS_SIZE_HPP
#define COMPONENTS_SIZE_HPP

struct Size final {
	Size(int w, int h) : w(w), h(h) {}
	int w;
	int h;
};

#endif