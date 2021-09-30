#ifndef SYSTEMS_BODY_HPP
#define SYSTEMS_BODY_HPP

#include <entityx/entityx.h>
#include <box2d/box2d.h>

class BodySystem final : public entityx::System<BodySystem> {
public:
	BodySystem(b2World *world);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	b2World *world;
};

#endif