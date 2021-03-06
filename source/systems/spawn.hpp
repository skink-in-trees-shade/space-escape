#ifndef SYSTEMS_SPAWN_HPP
#define SYSTEMS_SPAWN_HPP

#include <entityx/entityx.h>
#include "core/resource.hpp"
#include "entities/factory.hpp"

class SpawnSystem final : public entityx::System<SpawnSystem> {
public:
	SpawnSystem(EntityFactory *factory, Resource *resource, int round);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	EntityFactory *factory;
	Resource *resource;
	int round;
};

#endif