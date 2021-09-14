#include "systems/physics.hpp"
#include "systems/render.hpp"
#include "systems/spawn.hpp"
#include "game.hpp"

Game::Game(Window &window, World &world, Timer &timer) : window(window), world(world), timer(timer) {
	systems.add<PhysicsSystem>(world);
	systems.add<RenderSystem>(window);
	systems.add<SpawnSystem>(world);
	systems.configure();
}

void Game::run() {
	constexpr entityx::TimeDelta dt = 1.0 / 60.0;
	entityx::TimeDelta time = 0.0;
	entityx::TimeDelta acc = 0.0;
	entityx::TimeDelta prev = timer.time();
	entityx::TimeDelta curr = 0.0;
	entityx::TimeDelta frame = 0.0;

	while (window.is_open()) {
		window.poll_events();

		curr = timer.time();
		frame = curr - prev;
		prev = curr;
		acc += frame;

		while (acc >= dt) {
			systems.update<SpawnSystem>(dt);
			systems.update<PhysicsSystem>(dt);
			acc -= dt;
			time += dt;
		}

		systems.update<RenderSystem>(time);
	}
}