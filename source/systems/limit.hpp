#ifndef SYSTEMS_LIMIT_HPP
#define SYSTEMS_LIMIT_HPP

#include <entityx/entityx.h>

class LimitSystem final : public entityx::System<LimitSystem> {
public:
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);
};

#endif