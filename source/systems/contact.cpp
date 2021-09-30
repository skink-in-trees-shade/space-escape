#include "components/physics.hpp"
#include "components/breakable.hpp"
#include "contact.hpp"

ContactSystem::ContactSystem(b2World *world) : world(world) {
	world->SetContactListener(this);
}

void ContactSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (!bodies.empty()) {
		entities.each<Physics, Breakable>([this](entityx::Entity entity, Physics &physics, Breakable &breakable) {
			for (const b2Body *collided : bodies) {
				if (collided == physics.body) {
					world->DestroyBody(physics.body);
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