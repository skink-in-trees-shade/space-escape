#include "world.hpp"

World::World() : world(new b2World(b2Vec2_zero)) {
}

World::~World() {
	world->~b2World();
}