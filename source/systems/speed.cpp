#include "components/physics.hpp"
#include "components/speed.hpp"
#include "speed.hpp"

void SpeedSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Speed, Physics>([](entityx::Entity entity, Speed &speed, Physics &physics) {
		b2Vec2 velocity = physics.body->GetLinearVelocity();
		float length = velocity.Normalize();
		if (length == 0.0f) {
			velocity = b2Vec2(1.0f, 1.0f);
		}
		physics.body->SetLinearVelocity(speed.v * velocity);
	});
}