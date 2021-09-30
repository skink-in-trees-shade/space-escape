#include "components/physics.hpp"
#include "components/speed.hpp"
#include "speed.hpp"

void SpeedSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Speed, Physics>([](entityx::Entity entity, Speed &speed, Physics &physics) {
		physics.body->SetLinearVelocity(b2Vec2(speed.vx, speed.vy));
		entity.component<Speed>().remove();
	});
}