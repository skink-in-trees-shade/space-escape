#ifndef SYSTEMS_ANIMATION_HPP
#define SYSTEMS_ANIMATION_HPP

#include <entityx/entityx.h>
#include <box2d/box2d.h>

class AnimationSystem final : public entityx::System<AnimationSystem> {
public:
	AnimationSystem(b2World *world);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	b2World *world;
};

#endif