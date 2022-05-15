#include <string>
#include "components/collided.hpp"
#include "components/score.hpp"
#include "components/message.hpp"
#include "score.hpp"

void ScoreSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
	entities.each<Message, Score>([&](entityx::Entity entity, Message &message, Score &score) {
		entities.each<Collided, Score>([&](entityx::Entity sourceEntity, Collided &collided, Score &source) {
			score.points += source.points;
			message.text = std::to_string(score.points);
		});
	});
}