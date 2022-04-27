#ifndef COMPONENTS_RENDERABLE_HPP
#define COMPONENTS_RENDERABLE_HPP

enum class Sprite {
	Background,
	Ball,
	Brick,
	StrongBrick,
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