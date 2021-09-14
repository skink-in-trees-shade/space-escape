#ifndef SYSTEM_PHYSICS_HPP
#define SYSTEM_PHYSICS_HPP

#include <entityx/entityx.h>
#include "core/world.hpp"

class PhysicsSystem final : public entityx::System<PhysicsSystem> {
public:
	PhysicsSystem(World &world);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	World &world;
};

#endif