#include "components/material.hpp"
#include "components/physics.hpp"
#include "components/position.hpp"
#include "components/size.hpp"
#include "core/config.hpp"
#include "body.hpp"

BodySystem::BodySystem(b2World *world) : world(world) {
}

void BodySystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Material, Size, Position>([this](entityx::Entity entity, Material &material, Size &size, Position &position) {
		if (!entity.has_component<Physics>()) {
			b2BodyDef body_def;
			switch (material.body) {
			case Body::Static:
				body_def.type = b2_staticBody;
				break;
			case Body::Kinematic:
				body_def.type = b2_kinematicBody;
				break;
			case Body::Dynamic:
				body_def.type = b2_dynamicBody;
				break;
			}
			body_def.fixedRotation = true;
			body_def.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
			b2Body *body = world->CreateBody(&body_def);

			b2FixtureDef fixture_def;
			b2PolygonShape polygon_def;
			b2CircleShape circle_def;
			switch (material.shape) {
			case Shape::Polygon: {
				polygon_def.SetAsBox(size.w / 2.0f / PTM_RATIO, size.h / 2.0f / PTM_RATIO);
				fixture_def.shape = &polygon_def;
			} break;
			case Shape::Circle: {
				circle_def.m_radius = size.w / 2.0f / PTM_RATIO;
				fixture_def.shape = &circle_def;
			} break;
			}
			fixture_def.density = material.density;
			fixture_def.friction = material.friction;
			fixture_def.restitution = material.restitution;
			body->CreateFixture(&fixture_def);

			entity.assign<Physics>(body);
			entity.remove<Material>();
		}
	});
}