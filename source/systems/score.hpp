#ifndef SYSTEMS_SCORE_HPP
#define SYSTEMS_SCORE_HPP

#include <entityx/entityx.h>

class ScoreSystem final : public entityx::System<ScoreSystem> {
public:
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);
};

#endif