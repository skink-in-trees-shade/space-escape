#include <algorithm>
#include "components/physics.hpp"
#include "components/breakable.hpp"
#include "components/collided.hpp"
#include "core/config.hpp"
#include "contact.hpp"

ContactSystem::ContactSystem(b2World *world) : world(world) {
	world->SetContactListener(this);
}

void ContactSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	if (!bodies.empty()) {
		entities.each<Physics, Breakable>([&](entityx::Entity entity, Physics &physics, Breakable &breakable) {
			if (std::find(bodies.begin(), bodies.end(), physics.body) != bodies.end()) {
				entity.assign<Collided>();
			}
		});
		bodies.clear();
	}
}

void ContactSystem::BeginContact(b2Contact *contact) {
	bodies.push_back(contact->GetFixtureA()->GetBody());
	bodies.push_back(contact->GetFixtureB()->GetBody());
}