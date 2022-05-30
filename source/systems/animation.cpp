#include <algorithm>
#include "components/animation.hpp"
#include "components/collided.hpp"
#include "animation.hpp"

struct Noway final {
};

void AnimationSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Collided>([](entityx::Entity entity, Collided &collided) {
		if (!entity.has_component<Noway>()) {
			entity.assign<Animation>(std::vector<std::tuple<int, Color>>{
										 {2, {255, 255, 255}},
										 {4, {192, 192, 192}},
										 {6, {128, 128, 128}},
										 {8, {64, 64, 64}}},
									 10);
			entity.remove<Collided>();
		}
	});

	entities.each<Animation, Color>([](entityx::Entity entity, Animation &animation, Color &color) {
		animation.current++;
		auto frame = std::find_if(animation.frames.begin(), animation.frames.end(), [=](const std::tuple<int, Color> &f) { return std::get<0>(f) == animation.current; });
		if (frame != animation.frames.end()) {
			Color c = std::get<1>(*frame);
			color.r = c.r;
			color.g = c.g;
			color.b = c.b;
		}
		if (animation.current >= animation.total) {
			entity.remove<Animation>();
			entity.assign<Collided>();
			entity.assign<Noway>();
		}
	});
}