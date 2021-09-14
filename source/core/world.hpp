#ifndef CORE_WORLD_HPP
#define CORE_WORLD_HPP

#include <box2d/box2d.h>

#define PTM_RATIO 32.0

class PhysicsSystem;
class SpawnSystem;

class World final {
	friend class PhysicsSystem;
	friend class SpawnSystem;

public:
	World();
	~World();

private:
	b2World *world;
};

#endif