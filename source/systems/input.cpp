#include <SDL2/SDL.h>
#include "components/body.hpp"
#include "components/controlled.hpp"
#include "input.hpp"

void InputSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	constexpr double dv = 5;

	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	double vx = 0.0;
	if (state[SDL_SCANCODE_LEFT]) {
		vx -= dv;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		vx += dv;
	}

	entities.each<Controlled, Body>([vx](entityx::Entity entity, Controlled &controlled, Body &body) {
		body.body->SetLinearVelocity(b2Vec2(vx, 0));
	});
}