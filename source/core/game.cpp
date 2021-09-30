#include "game.hpp"

Game::Game(
	std::shared_ptr<RenderSystem> render,
	std::shared_ptr<InputSystem> input,
	std::shared_ptr<LimitSystem> limit,
	std::shared_ptr<PhysicsSystem> physics,
	std::shared_ptr<ContactSystem> contact,
	std::shared_ptr<SpawnSystem> spawn,
	std::shared_ptr<BodySystem> body,
	std::shared_ptr<SpeedSystem> speed) {
	systems.add(render);
	systems.add(input);
	systems.add(limit);
	systems.add(physics);
	systems.add(contact);
	systems.add(spawn);
	systems.add(body);
	systems.add(speed);
	systems.configure();
}

void Game::run() {
	double prev = SDL_GetTicks() / 1000.0;
	double acc = 0.0;
	double curr = 0.0;

	is_running = true;
	while (is_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				is_running = false;
			}
		}

		if (is_running) {
			curr = SDL_GetTicks() / 1000.0;
			acc += curr - prev;
			prev = curr;

			constexpr double dt = 1.0 / 60.0;
			int iter = acc / dt;
			for (int i = 0; i < iter; i++) {
				systems.update<InputSystem>(dt);
				systems.update<LimitSystem>(dt);
				systems.update<PhysicsSystem>(dt);
				systems.update<ContactSystem>(dt);
				systems.update<SpawnSystem>(dt);
				systems.update<BodySystem>(dt);
				systems.update<SpeedSystem>(dt);
			}
			acc -= iter * dt;

			systems.update<RenderSystem>(iter * dt);
		}
	}
}