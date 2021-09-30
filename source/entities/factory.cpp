#include <map>
#include "components/breakable.hpp"
#include "components/controlled.hpp"
#include "components/limited.hpp"
#include "components/material.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/size.hpp"
#include "core/config.hpp"
#include "factory.hpp"

void EntityFactory::create_background(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Size>(WINDOW_WIDTH, WINDOW_HEIGHT);
	entity.assign<Position>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	entity.assign<Renderable>(Sprite::Background);
}

void EntityFactory::create_ball(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Dynamic, Shape::Circle, 1.0f, 0.0f, 1.0f);
	entity.assign<Size>(4, 4);
	entity.assign<Position>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 24);
	entity.assign<Renderable>(Sprite::Ball);
	entity.assign<Limited>(160, 64, 64);
}

void EntityFactory::create_brick(entityx::EntityManager &entities, Brick brick) {
	static std::map<Brick, Sprite> sprites = {
		{Brick::One, Sprite::BrickOne},
		{Brick::Two, Sprite::BrickTwo},
		{Brick::Three, Sprite::BrickThree},
	};

	constexpr int w = 10, h = 6;
	static int sx = 6 + w / 2, sy = h * 6;
	int x = sx, y = sy;
	sx += w;
	if (sx >= WINDOW_WIDTH - 6) {
		sx = 6 + w / 2;
		sy += h * 2;
	}

	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Static, Shape::Polygon, 10.0f, 0.0f, 0.1f);
	entity.assign<Size>(10, 6);
	entity.assign<Position>(x, y);
	entity.assign<Renderable>(sprites[brick]);
	if (brick != Brick::One) {
		entity.assign<Breakable>();
	}
}

void EntityFactory::create_paddle(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Dynamic, Shape::Polygon, 10.0f, 0.4f, 0.1f);
	entity.assign<Size>(20, 6);
	entity.assign<Position>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 12);
	entity.assign<Renderable>(Sprite::Paddle);
	entity.assign<Controlled>();
}

void EntityFactory::create_wall(entityx::EntityManager &entities, Wall wall) {
	entityx::Entity entity = entities.create();

	constexpr int s = 6;
	int x, y, w, h;
	Sprite sprite;
	switch (wall) {
	case Wall::Top:
		x = WINDOW_WIDTH / 2;
		y = s / 2;
		w = WINDOW_WIDTH;
		h = s;
		sprite = Sprite::WallTop;
		break;
	case Wall::Bottom:
		x = WINDOW_WIDTH / 2;
		y = WINDOW_HEIGHT - s / 2;
		w = WINDOW_WIDTH;
		h = s;
		sprite = Sprite::WallBottom;
		break;
	case Wall::Left:
		x = s / 2;
		y = WINDOW_HEIGHT / 2;
		w = s;
		h = WINDOW_HEIGHT;
		sprite = Sprite::WallLeft;
		break;
	case Wall::Right:
		x = WINDOW_WIDTH - s / 2;
		y = WINDOW_HEIGHT / 2;
		w = s;
		h = WINDOW_HEIGHT;
		sprite = Sprite::WallRight;
		break;
	}

	entity.assign<Material>(Body::Static, Shape::Polygon, 0.0f, 0.0f, 0.0f);
	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Renderable>(sprite);
}