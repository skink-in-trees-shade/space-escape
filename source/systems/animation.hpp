#ifndef SYSTEMS_ANIMATION_HPP
#define SYSTEMS_ANIMATION_HPP

#include <entityx/entityx.h>

class AnimationSystem final : public entityx::System<AnimationSystem> {
public:
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);
};

#endif