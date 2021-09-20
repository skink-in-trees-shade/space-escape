#ifndef COMPONENTS_LIMITED_HPP
#define COMPONENTS_LIMITED_HPP

struct Limited final {
	Limited(float v, float vx, float vy) : v(v), vx(vx), vy(vy) {}
	float v;
	float vx;
	float vy;
};

#endif