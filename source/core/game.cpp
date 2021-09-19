#include "game.hpp"

Game::Game(std::shared_ptr<RenderSystem> render, std::shared_ptr<PhysicsSystem> physics, std::shared_ptr<SpawnSystem> spawn) {
	systems.add(render);
	systems.add(physics);
	systems.add(spawn);
	systems.configure();
}

void Game::run() {
	bool is_running = true;
	constexpr entityx::TimeDelta dt = 1.0 / 60.0;
	entityx::TimeDelta time = 0.0;
	entityx::TimeDelta acc = 0.0;
	entityx::TimeDelta prev = SDL_GetTicks() / 1000.0;
	entityx::TimeDelta curr = 0.0;
	entityx::TimeDelta frame = 0.0;

	while (is_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				is_running = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					is_running = false;
					break;
				default:
					break;
				}
				break;
			}
		}

		curr = SDL_GetTicks() / 1000.0;
		frame = curr - prev;
		prev = curr;
		acc += frame;

		while (acc >= dt) {
			acc -= dt;
			time += dt;
			systems.update<SpawnSystem>(dt);
			systems.update<PhysicsSystem>(dt);
		}

		systems.update<RenderSystem>(time);
	}
}