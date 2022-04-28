#include <fruit/fruit.h>
#include "systems/body.hpp"
#include "systems/contact.hpp"
#include "systems/limit.hpp"
#include "systems/input.hpp"
#include "systems/physics.hpp"
#include "systems/render.hpp"
#include "systems/spawn.hpp"
#include "systems/speed.hpp"
#include "entities/factory.hpp"
#include "core/common.hpp"
#include "core/game.hpp"

fruit::Component<Game> getGameComponent() {
	return fruit::createComponent()
		.registerConstructor<Common()>()
		.registerConstructor<EntityFactory()>()
		.registerProvider([](Common *common) { return new RenderSystem(common->renderer); })
		.registerConstructor<InputSystem()>()
		.registerConstructor<LimitSystem()>()
		.registerProvider([](Common *common) { return new PhysicsSystem(common->world); })
		.registerProvider([](Common *common) { return new ContactSystem(common->world); })
		.registerProvider([](EntityFactory *factory) { return new SpawnSystem(factory, 1); })
		.registerProvider([](Common *common) { return new BodySystem(common->world); })
		.registerConstructor<SpeedSystem()>()
		.registerConstructor<Game(
			std::shared_ptr<RenderSystem>,
			std::shared_ptr<InputSystem>,
			std::shared_ptr<LimitSystem>,
			std::shared_ptr<PhysicsSystem>,
			std::shared_ptr<ContactSystem>,
			std::shared_ptr<SpawnSystem>,
			std::shared_ptr<BodySystem>,
			std::shared_ptr<SpeedSystem>)>();
}

int main(int argc, char *argv[]) {
	fruit::Injector<Game> injector(getGameComponent);
	Game *game = injector.get<Game *>();
	game->run();
	return 0;
}