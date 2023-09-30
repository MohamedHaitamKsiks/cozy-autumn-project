#ifndef SYSTEM_PHYSICSSYSTEM2D_H
#define SYSTEM_PHYSICSSYSTEM2D_H

#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"

#include "CollisionSystem2D.h"
#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class PhysicsSystem2D: public System<PhysicsBody2D, CollisionBox2D, Transform2D>
{
public:
	PhysicsSystem2D();

private:

	// move on one axis only
	void MoveAndCollide(PhysicsBody2D& physicsBody2D, CollisionBox2D& collisionBox2D, Transform2D& transform2D, const vec2& axis, float delta);

	// default methods
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PHYSICSSYSTEM2D_H