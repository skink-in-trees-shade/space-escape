#include <string>
#include "components/physics.hpp"
#include "components/breakable.hpp"
#include "components/score.hpp"
#include "components/message.hpp"
#include "components/life.hpp"
#include "components/deadly.hpp"
#include "core/config.hpp"
#include "contact.hpp"

ContactSystem::ContactSystem(b2World *world) : world(world) {
	world->SetContactListener(this);
}

void ContactSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (!bodies.empty()) {
		entities.each<Deadly>([&](entityx::Entity entity, Deadly &deadly) {
			for (const b2Body *collided : bodies) {
				if (collided == physics.body) {
					entities.each<Life>
				}
			}
		});

		entities.each<Physics, Breakable, Score>([&](entityx::Entity entity, Physics &physics, Breakable &breakable, Score &score) {
			for (const b2Body *collided : bodies) {
				if (collided == physics.body) {
					world->DestroyBody(physics.body);

					entities.each<Message, Score>([&](entityx::Entity targetEntity, Message &targetMessage, Score &targetScore) {
						targetScore.points += score.points;
						targetMessage.text = std::to_string(targetScore.points);
					});

					entity.destroy();
				}
			}
		});
		bodies.clear();
	}
}

void ContactSystem::BeginContact(b2Contact *contact) {
	bodies.push_back(contact->GetFixtureA()->GetBody());
	bodies.push_back(contact->GetFixtureB()->GetBody());
}