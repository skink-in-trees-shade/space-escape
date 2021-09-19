#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include <entityx/entityx.h>
#include "systems/physics.hpp"
#include "systems/render.hpp"
#include "systems/spawn.hpp"

class Game final : private entityx::EntityX {
public:
	Game(std::shared_ptr<RenderSystem> render, std::shared_ptr<PhysicsSystem> physics, std::shared_ptr<SpawnSystem> spawn);
	void run();
};

#endif