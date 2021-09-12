#include "systems/render.hpp"
#include "game.hpp"

Game::Game(Window &window, Timer &timer) : window(window), timer(timer) {
	systems.add<RenderSystem>(window);
	systems.configure();
}

void Game::run() {
	constexpr entityx::TimeDelta dt = 1000.0 / 60.0;
	entityx::TimeDelta time = 0.0;
	entityx::TimeDelta acc = 0.0;
	entityx::TimeDelta prev = timer.time();
	entityx::TimeDelta curr = 0.0;
	entityx::TimeDelta frame = 0.0;

	while (window.is_open()) {
		curr = timer.time();
		frame = curr - prev;
		prev = curr;

		acc += frame;

		window.poll_events();

		while (acc >= dt) {
			systems.update_all(acc); // update

			acc -= dt;
			time += dt;
		}

		systems.update<RenderSystem>(acc);
	}
}