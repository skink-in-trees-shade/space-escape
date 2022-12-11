#include <vector>
#include "components/animation.hpp"
#include "components/collided.hpp"
#include "components/color.hpp"
#include "components/physics.hpp"
#include "core/config.hpp"
#include "animation.hpp"

AnimationSystem::AnimationSystem(b2World *world) : world(world) {
}

void AnimationSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Collided, Physics>([this](entityx::Entity entity, Collided &collided, Physics &physics) {
		entity.assign<Animation>(std::vector<Color> ANIMATION_DESTRUCTION);
		world->DestroyBody(physics.body);
		entity.remove<Physics>();
	});

	entities.each<Animation, Color>([](entityx::Entity entity, Animation &animation, Color &color) {
		animation.current++;
		if (animation.current < animation.frames.size()) {
			color = animation.frames.at(animation.current);
		} else {
			entity.remove<Animation>();
			if (entity.has_component<Collided>()) {
				entity.destroy();
			}
		}
	});
}