#ifndef SYSTEM_SPAWN_HPP
#define SYSTEM_SPAWN_HPP

#include <entityx/entityx.h>
#include "entities/factory.hpp"

class SpawnSystem final : public entityx::System<SpawnSystem> {
public:
	SpawnSystem(EntityFactory *factory);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	EntityFactory *factory;
	bool entities_spawned;
};

#endif