#ifndef COMPONENTS_SPEED_HPP
#define COMPONENTS_SPEED_HPP

struct Speed final {
	Speed(float vx, float vy) : vx(vx), vy(vy) {}
	float vx;
	float vy;
};

#endif