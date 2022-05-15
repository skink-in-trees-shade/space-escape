#ifndef SYSTEMS_DESTRUCTION_HPP
#define SYSTEMS_DESTRUCTION_HPP

#include <entityx/entityx.h>
#include <box2d/box2d.h>

class DestructionSystem final : public entityx::System<DestructionSystem> {
public:
	DestructionSystem(b2World *world);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	b2World *world;
};

#endif