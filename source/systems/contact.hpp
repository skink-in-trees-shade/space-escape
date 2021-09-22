#ifndef SYSTEMS_CONTACT_HPP
#define SYSTEMS_CONTACT_HPP

#include <entityx/entityx.h>
#include <box2d/box2d.h>

class ContactSystem final : public entityx::System<ContactSystem>, public b2ContactListener {
public:
	ContactSystem(b2World *world);
	void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt);
	void BeginContact(b2Contact *contact);

private:
	b2World *world;
	std::vector<b2Body *> bodies = {};
};

#endif