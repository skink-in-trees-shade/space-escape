#include <string>
#include "components/breakable.hpp"
#include "components/color.hpp"
#include "components/controlled.hpp"
#include "components/joint.hpp"
#include "components/limited.hpp"
#include "components/material.hpp"
#include "components/message.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/size.hpp"
#include "components/score.hpp"
#include "components/speed.hpp"
#include "core/config.hpp"
#include "factory.hpp"

void EntityFactory::create_background(entityx::EntityManager &entities, int n) {
	constexpr static Sprite backgrounds[] = {Sprite::Background1, Sprite::Background2};
	entityx::Entity entity = entities.create();
	entity.assign<Size>(SCREEN_WIDTH, SCREEN_HEIGHT);
	entity.assign<Position>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	entity.assign<Renderable>(backgrounds[n]);
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

void EntityFactory::create_brick(entityx::EntityManager &entities, int x, int y, bool strong, int r, int g, int b, int points) {
	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Static, Shape::Polygon, 10.0f, 0.0f, 0.1f);
	entity.assign<Size>(BRICK_WIDTH, BRICK_HEIGHT);
	entity.assign<Position>(WALL_THICKNESS + (BRICK_WIDTH / 2) + (x * BRICK_WIDTH), WALL_THICKNESS + (BRICK_HEIGHT / 2) + (y * BRICK_HEIGHT));
	entity.assign<Renderable>(strong ? Sprite::StrongBrick : Sprite::Brick);
	entity.assign<Color>(r, g, b);
	entity.assign<Score>(points);
	if (!strong) {
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
	entity.assign<Joint>();
	entity.assign<Score>(0);
}

void EntityFactory::create_wall(entityx::EntityManager &entities, int x, int y, int w, int h) {
	entityx::Entity entity = entities.create();
	entity.assign<Material>(Body::Static, Shape::Polygon, 0.0f, 0.0f, 0.0f);
	entity.assign<Size>(w, h);
	entity.assign<Position>(x, y);
	if (y < SCREEN_HEIGHT / 2) {
		entity.assign<Renderable>(Sprite::WallTop);
	} else if (y > SCREEN_HEIGHT / 2) {
		entity.assign<Renderable>(Sprite::WallBottom);
	} else if (x < SCREEN_WIDTH / 2) {
		entity.assign<Renderable>(Sprite::WallLeft);
	} else if (x > SCREEN_WIDTH / 2) {
		entity.assign<Renderable>(Sprite::WallRight);
	}
	entity.assign<Color>(COLOR_MAIN);
}

void EntityFactory::create_round_title_message(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Message>("ROUND");
	entity.assign<Position>(SCREEN_WIDTH + GLYPH_WIDTH, GLYPH_HEIGHT);
	entity.assign<Color>(COLOR_MAIN);
}

void EntityFactory::create_round_number_message(entityx::EntityManager &entities, int round) {
	entityx::Entity entity = entities.create();
	entity.assign<Message>(std::to_string(round));
	entity.assign<Position>(SCREEN_WIDTH + GLYPH_WIDTH, GLYPH_HEIGHT * 2);
}

void EntityFactory::create_score_title_message(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Message>("SCORE");
	entity.assign<Position>(SCREEN_WIDTH + GLYPH_WIDTH, GLYPH_HEIGHT * 4);
	entity.assign<Color>(COLOR_MAIN);
}

void EntityFactory::create_score_points_message(entityx::EntityManager &entities) {
	entityx::Entity entity = entities.create();
	entity.assign<Score>(0);
	entity.assign<Message>("0");
	entity.assign<Position>(SCREEN_WIDTH + GLYPH_WIDTH, GLYPH_HEIGHT * 5);
}

void EntityFactory::create_brick_one(entityx::EntityManager &entities, int x, int y) {
	create_brick(entities, x, y, true, COLOR_ACTIVE_1, 0);
}

void EntityFactory::create_brick_two(entityx::EntityManager &entities, int x, int y) {
	create_brick(entities, x, y, false, COLOR_ACTIVE_2, 20);
}

void EntityFactory::create_brick_three(entityx::EntityManager &entities, int x, int y) {
	create_brick(entities, x, y, false, COLOR_ACTIVE_3, 10);
}

void EntityFactory::create_top_wall(entityx::EntityManager &entities) {
	create_wall(entities, SCREEN_WIDTH / 2, WALL_THICKNESS / 2, SCREEN_WIDTH, WALL_THICKNESS);
}

void EntityFactory::create_bottom_wall(entityx::EntityManager &entities) {
	create_wall(entities, SCREEN_WIDTH / 2, SCREEN_HEIGHT - (WALL_THICKNESS / 2), SCREEN_WIDTH, WALL_THICKNESS);
}

void EntityFactory::create_left_wall(entityx::EntityManager &entities) {
	create_wall(entities, WALL_THICKNESS / 2, SCREEN_HEIGHT / 2, WALL_THICKNESS, SCREEN_HEIGHT);
}

void EntityFactory::create_right_wall(entityx::EntityManager &entities) {
	create_wall(entities, SCREEN_WIDTH - (WALL_THICKNESS / 2), SCREEN_HEIGHT / 2, WALL_THICKNESS, SCREEN_HEIGHT);
}
