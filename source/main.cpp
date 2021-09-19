#include <fruit/fruit.h>
#include "systems/physics.hpp"
#include "systems/render.hpp"
#include "systems/spawn.hpp"
#include "entities/factory.hpp"
#include "core/common.hpp"
#include "core/game.hpp"

fruit::Component<Game> getGameComponent() {
	return fruit::createComponent()
		.registerConstructor<Common()>()
		.registerProvider([](Common *common) { return new PhysicsSystem(common->world); })
		.registerProvider([](Common *common) { return new RenderSystem(common->renderer); })
		.registerProvider([](EntityFactory *factory) { return new SpawnSystem(factory); })
		.registerProvider([](Common *common) { return new EntityFactory(common->world, common->renderer); })
		.registerConstructor<Game(std::shared_ptr<RenderSystem>, std::shared_ptr<PhysicsSystem>, std::shared_ptr<SpawnSystem>)>();
}

int main(int argc, char *argv[]) {
	fruit::Injector<Game> injector(getGameComponent);
	Game *game = injector.get<Game *>();
	game->run();
	return 0;
}