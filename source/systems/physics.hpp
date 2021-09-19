#ifndef SYSTEM_PHYSICS_HPP
#define SYSTEM_PHYSICS_HPP

#include <entityx/entityx.h>
#include <box2d/box2d.h>

class PhysicsSystem final : public entityx::System<PhysicsSystem> {
public:
	PhysicsSystem(b2World *world);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	b2World *world;
};

#endif