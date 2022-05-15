#ifndef SYSTEMS_JOINT_HPP
#define SYSTEMS_JOINT_HPP

#include <entityx/entityx.h>
#include <box2d/box2d.h>

class JointSystem final : public entityx::System<JointSystem> {
public:
	JointSystem(b2World *world);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	b2World *world;
};

#endif