#ifndef SYSTEM_SPAWN_HPP
#define SYSTEM_SPAWN_HPP

#include <entityx/entityx.h>
#include "core/window.hpp"
#include "core/world.hpp"

class SpawnSystem final : public entityx::System<SpawnSystem> {
public:
	SpawnSystem(World &world, Window &window);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	World &world;
	Window &window;
	bool entities_spawned;
};

#endif