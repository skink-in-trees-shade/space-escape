#ifndef SYSTEMS_SPEED_HPP
#define SYSTEMS_SPEED_HPP

#include <entityx/entityx.h>

class SpeedSystem final : public entityx::System<SpeedSystem> {
public:
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);
};

#endif