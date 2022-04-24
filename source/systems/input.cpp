#include <SDL2/SDL.h>
#include "components/controlled.hpp"
#include "components/physics.hpp"
#include "core/config.hpp"
#include "input.hpp"

void InputSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	double vx = 0.0;
	if (state[SDL_SCANCODE_LEFT]) {
		vx -= PADDLE_DELTA_VELOCITY;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		vx += PADDLE_DELTA_VELOCITY;
	}

	entities.each<Controlled, Physics>([vx](entityx::Entity entity, Controlled &controlled, Physics &physics) {
		physics.body->SetLinearVelocity(b2Vec2(vx, 0));
	});
}