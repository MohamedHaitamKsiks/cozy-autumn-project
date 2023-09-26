#ifndef COMPONENT_PHYSICSBODY2D_H
#define COMPONENT_PHYSICSBODY2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct PhysicsBody2D: public TComponent<PhysicsBody2D>
{
	vec2 Velocity = vec2::ZERO();
	bool IsStatic = false;
};

#endif // COMPONENT_PHYSICSBODY2D_H