#ifndef COMPONENTS_MATERIAL_HPP
#define COMPONENTS_MATERIAL_HPP

enum class Body {
	Static,
	Kinematic,
	Dynamic,
};

enum class Shape {
	Polygon,
	Circle,
};

struct Material final {
	Material(Body body, Shape shape, float density, float friction, float restitution) : body(body), shape(shape), density(density), friction(friction), restitution(restitution) {}
	Body body;
	Shape shape;
	float density;
	float friction;
	float restitution;
};

#endif