#include <string>
#include <fruit/fruit.h>
#include "systems/body.hpp"
#include "systems/contact.hpp"
#include "systems/destruction.hpp"
#include "systems/joint.hpp"
#include "systems/limit.hpp"
#include "systems/input.hpp"
#include "systems/physics.hpp"
#include "systems/render.hpp"
#include "systems/score.hpp"
#include "systems/spawn.hpp"
#include "systems/speed.hpp"
#include "entities/factory.hpp"
#include "core/common.hpp"
#include "core/game.hpp"
#include "core/resource.hpp"

fruit::Component<Game> getGameComponent(const int round) {
	const static int _round = round;
	return fruit::createComponent()
		.registerConstructor<Common()>()
		.registerProvider([](Common *common) { return new Resource(common->renderer); })
		.registerConstructor<EntityFactory()>()
		.registerProvider([](Common *common, Resource *resource) { return new RenderSystem(common->renderer, resource); })
		.registerConstructor<InputSystem()>()
		.registerConstructor<LimitSystem()>()
		.registerProvider([](Common *common) { return new PhysicsSystem(common->world); })
		.registerProvider([](Common *common) { return new ContactSystem(common->world); })
		.registerProvider([](EntityFactory *factory, Resource *resource) { return new SpawnSystem(factory, resource, _round); })
		.registerProvider([](Common *common) { return new BodySystem(common->world); })
		.registerProvider([](Common *common) { return new JointSystem(common->world); })
		.registerConstructor<SpeedSystem()>()
		.registerConstructor<ScoreSystem()>()
		.registerProvider([](Common *common) { return new DestructionSystem(common->world); })
		.registerConstructor<Game(
			std::shared_ptr<RenderSystem>,
			std::shared_ptr<InputSystem>,
			std::shared_ptr<LimitSystem>,
			std::shared_ptr<PhysicsSystem>,
			std::shared_ptr<ContactSystem>,
			std::shared_ptr<SpawnSystem>,
			std::shared_ptr<BodySystem>,
			std::shared_ptr<JointSystem>,
			std::shared_ptr<SpeedSystem>,
			std::shared_ptr<ScoreSystem>,
			std::shared_ptr<DestructionSystem>)>();
}

int main(int argc, char *argv[]) {
	const int round = argc >= 2 ? std::stoi(argv[1]) : 1;
	fruit::Injector<Game> injector(getGameComponent, round);
	Game *game(injector);
	game->run();
	return 0;
}