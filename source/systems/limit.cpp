#include "components/physics.hpp"
#include "components/limited.hpp"
#include "core/config.hpp"
#include "limit.hpp"

void LimitSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Physics, Limited>([](entityx::Entity entity, Physics &physics, Limited &limited) {
		b2Vec2 velocity = physics.body->GetLinearVelocity();
		bool adjusted = false;
		if (velocity.x > -limited.vx / PTM_RATIO && velocity.x < limited.vx / PTM_RATIO) {
			velocity.x = -limited.vx / PTM_RATIO;
			adjusted = true;
		}
		if (velocity.y > -limited.vy / PTM_RATIO && velocity.y < limited.vy / PTM_RATIO) {
			velocity.y = -limited.vy / PTM_RATIO;
			adjusted = true;
		}
		if (velocity.Length() > limited.v / PTM_RATIO) {
			velocity *= limited.v / PTM_RATIO / velocity.Length();
			adjusted = true;
		}
		if (adjusted) {
			physics.body->SetLinearVelocity(velocity);
		}
	});
}