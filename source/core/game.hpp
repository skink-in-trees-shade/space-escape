#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <entityx/entityx.h>
#include "systems/contact.hpp"
#include "systems/limit.hpp"
#include "systems/input.hpp"
#include "systems/physics.hpp"
#include "systems/render.hpp"
#include "systems/spawn.hpp"

class Game final : private entityx::EntityX {
public:
	Game(
		std::shared_ptr<RenderSystem> render,
		std::shared_ptr<InputSystem> input,
		std::shared_ptr<LimitSystem> limit,
		std::shared_ptr<PhysicsSystem> physics,
		std::shared_ptr<ContactSystem> contact,
		std::shared_ptr<SpawnSystem> spawn);
	void run();

private:
	bool is_running;
};

#endif