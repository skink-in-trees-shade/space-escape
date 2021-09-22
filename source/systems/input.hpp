#ifndef SYSTEMS_INPUT_HPP
#define SYSTEMS_INPUT_HPP

#include <entityx/entityx.h>

class InputSystem final : public entityx::System<InputSystem> {
public:
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);
};

#endif