#include <SDL_mixer.h>
#include "components/collided.hpp"
#include "sound.hpp"

SoundSystem::SoundSystem(Resource *resource) : resource(resource) {
}

void SoundSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	auto collided = entities.entities_with_components<Collided>();
	if (collided.begin() != collided.end()) {
		Mix_PlayChannel(-1, resource->sounds[Audio::Hit1], 0);
	}
}