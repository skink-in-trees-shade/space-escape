#ifndef COMPONENTS_RENDERABLE_HPP
#define COMPONENTS_RENDERABLE_HPP

enum class Sprite {
	Background,
	Ball,
	BrickOne,
	BrickTwo,
	BrickThree,
	Paddle,
	WallLeft,
	WallRight,
	WallTop,
	WallBottom,
};

struct Renderable final {
	Renderable(Sprite sprite) : sprite(sprite) {}
	Sprite sprite;
};

#endif