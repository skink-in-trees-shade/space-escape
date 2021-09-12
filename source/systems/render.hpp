#ifndef SYSTEM_RENDER_HPP
#define SYSTEM_RENDER_HPP

#include <entityx/entityx.h>
#include "core/window.hpp"

class RenderSystem final : public entityx::System<RenderSystem> {
public:
	RenderSystem(Window &window);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);

private:
	Window &window;
};

#endif