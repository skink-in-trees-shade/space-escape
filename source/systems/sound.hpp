#ifndef SYSTEMS_SOUND_HPP
#define SYSTEMS_SOUND_HPP

#include <entityx/entityx.h>
#include "core/resource.hpp"

class SoundSystem final : public entityx::System<SoundSystem> {
public:
	SoundSystem(Resource *resource);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	Resource *resource;
};

#endif