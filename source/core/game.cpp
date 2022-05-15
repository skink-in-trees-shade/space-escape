#include "game.hpp"

Game::Game(
	std::shared_ptr<RenderSystem> render,
	std::shared_ptr<InputSystem> input,
	std::shared_ptr<LimitSystem> limit,
	std::shared_ptr<PhysicsSystem> physics,
	std::shared_ptr<ContactSystem> contact,
	std::shared_ptr<SpawnSystem> spawn,
	std::shared_ptr<BodySystem> body,
	std::shared_ptr<JointSystem> joint,
	std::shared_ptr<SpeedSystem> speed,
	std::shared_ptr<ScoreSystem> score,
	std::shared_ptr<DestructionSystem> destruction) {
	systems.add(render);
	systems.add(input);
	systems.add(limit);
	systems.add(physics);
	systems.add(contact);
	systems.add(spawn);
	systems.add(body);
	systems.add(joint);
	systems.add(speed);
	systems.add(score);
	systems.add(destruction);
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
				systems.update<JointSystem>(dt);
				systems.update<SpeedSystem>(dt);
				systems.update<ScoreSystem>(dt);
				systems.update<DestructionSystem>(dt);
			}
			acc -= iter * dt;

			systems.update<RenderSystem>(iter * dt);
		}
	}
}