#include <math.h>
#include "components/physics.hpp"
#include "components/speed.hpp"
#include "speed.hpp"

void SpeedSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Speed, Physics>([](entityx::Entity entity, Speed &speed, Physics &physics) {
		b2Vec2 velocity = physics.body->GetLinearVelocity();
		velocity.Normalize();
		const float min = 0.5f;
		if (fabs(velocity.x) < min) {
			velocity.x = copysignf(min, velocity.x);
		}
		if (fabs(velocity.y) < min) {
			velocity.y = copysignf(min, velocity.y);
		}
		physics.body->SetLinearVelocity(speed.v * velocity);
	});
}