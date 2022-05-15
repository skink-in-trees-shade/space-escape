#include "components/physics.hpp"
#include "components/joint.hpp"
#include "core/config.hpp"
#include "joint.hpp"

JointSystem::JointSystem(b2World *world) : world(world) {
}

void JointSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Physics, Joint>([this](entityx::Entity entity, Physics &physics, Joint &joint) {
		b2BodyDef floor_def;
		floor_def.type = b2_staticBody;
		floor_def.fixedRotation = true;
		floor_def.position.Set(SCREEN_WIDTH / 2.0f / PTM_RATIO, SCREEN_HEIGHT + 4 / 2 / PTM_RATIO);
		b2Body *floor = world->CreateBody(&floor_def);

		b2PrismaticJointDef joint_def;
		joint_def.collideConnected = true;
		joint_def.Initialize(physics.body, floor, physics.body->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
		world->CreateJoint(&joint_def);

		entity.remove<Joint>();
	});
}