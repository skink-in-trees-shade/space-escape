#include <map>
#include "components/breakable.hpp"
#include "components/color.hpp"
#include "components/controlled.hpp"
#include "components/limited.hpp"
#include "components/material.hpp"
#include "components/message.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/size.hpp"
#include "components/speed.hpp"
#include "core/config.hpp"
#include "factory.hpp"

void EntityFactory::create_background(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Size>(SCREEN_WIDTH, SCREEN_HEIGHT);
	entity.assign<Position>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	entity.assign<Renderable>(Sprite::Background);
}

void EntityFactory::create_ball(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Dynamic, Shape::Circle, 1.0f, 0.0f, 1.0f);
	entity.assign<Size>(BALL_WIDTH, BALL_HEIGHT);
	entity.assign<Position>(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (WALL_THICKNESS * 2) - PADDLE_HEIGHT);
	entity.assign<Renderable>(Sprite::Ball);
	entity.assign<Color>(COLOR_MAIN);
	entity.assign<Speed>(100, 100);
	entity.assign<Limited>(160, 64, 64);
}

void EntityFactory::create_brick(entityx::EntityManager &entities, Brick brick) {
	struct BrickData {
		Sprite sprite;
		int r;
		int g;
		int b;
	};
	static std::map<Brick, BrickData> sprites = {
		{Brick::One, {Sprite::StrongBrick, COLOR_ACTIVE_1}},
		{Brick::Two, {Sprite::Brick, COLOR_ACTIVE_2}},
		{Brick::Three, {Sprite::Brick, COLOR_ACTIVE_3}},
	};

	static int sx = WALL_THICKNESS + (BRICK_WIDTH / 2), sy = WALL_THICKNESS + BRICK_HEIGHT * 5;
	int x = sx, y = sy;
	sx += BRICK_WIDTH;
	if (sx >= SCREEN_WIDTH - WALL_THICKNESS) {
		sx = WALL_THICKNESS + (BRICK_WIDTH / 2);
		sy += BRICK_HEIGHT * 2;
	}

	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Static, Shape::Polygon, 10.0f, 0.0f, 0.1f);
	entity.assign<Size>(BRICK_WIDTH, BRICK_HEIGHT);
	entity.assign<Position>(x, y);
	entity.assign<Renderable>(sprites[brick].sprite);
	entity.assign<Color>(sprites[brick].r, sprites[brick].g, sprites[brick].b);
	if (brick != Brick::One) {
		entity.assign<Breakable>();
	}
}

void EntityFactory::create_paddle(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Dynamic, Shape::Polygon, 10.0f, 0.4f, 0.1f);
	entity.assign<Size>(PADDLE_WIDTH, PADDLE_HEIGHT);
	entity.assign<Position>(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (WALL_THICKNESS * 2));
	entity.assign<Renderable>(Sprite::Paddle);
	entity.assign<Color>(COLOR_MAIN);
	entity.assign<Controlled>();
}

void EntityFactory::create_wall(entityx::EntityManager &entities, Wall wall) {
	entityx::Entity entity = entities.create();

	int x, y, w, h;
	Sprite sprite;
	switch (wall) {
	case Wall::Top:
		x = SCREEN_WIDTH / 2;
		y = WALL_THICKNESS / 2;
		w = SCREEN_WIDTH;
		h = WALL_THICKNESS;
		sprite = Sprite::WallTop;
		break;
	case Wall::Bottom:
		x = SCREEN_WIDTH / 2;
		y = SCREEN_HEIGHT - (WALL_THICKNESS / 2);
		w = SCREEN_WIDTH;
		h = WALL_THICKNESS;
		sprite = Sprite::WallBottom;
		break;
	case Wall::Left:
		x = WALL_THICKNESS / 2;
		y = SCREEN_HEIGHT / 2;
		w = WALL_THICKNESS;
		h = SCREEN_HEIGHT;
		sprite = Sprite::WallLeft;
		break;
	case Wall::Right:
		x = SCREEN_WIDTH - (WALL_THICKNESS / 2);
		y = SCREEN_HEIGHT / 2;
		w = WALL_THICKNESS;
		h = SCREEN_HEIGHT;
		sprite = Sprite::WallRight;
		break;
	}

	entity.assign<Material>(Body::Static, Shape::Polygon, 0.0f, 0.0f, 0.0f);
	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	entity.assign<Renderable>(sprite);
	entity.assign<Color>(COLOR_MAIN);
}

void EntityFactory::create_round_title_message(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	std::string text = "ROUND";
	entity.assign<Message>(text);
	entity.assign<Position>(SCREEN_WIDTH + GLYPH_WIDTH, GLYPH_HEIGHT);
	entity.assign<Color>(COLOR_MAIN);
}

void EntityFactory::create_round_number_message(entityx::EntityManager &entities, int round) {
	entityx::Entity entity = entities.create();
	std::string text = std::to_string(round);
	entity.assign<Message>(text);
	entity.assign<Position>(SCREEN_WIDTH + GLYPH_WIDTH, GLYPH_HEIGHT * 2);
}