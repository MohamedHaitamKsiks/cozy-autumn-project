#ifndef SYSTEM_SPRINGCOLLISIONSYSTEM_H
#define SYSTEM_SPRINGCOLLISIONSYSTEM_H

#include "ASEngine.h"

#include "components/Objects/Spring.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/PhysicsSystem2D/CollisionSystem2D.h"

using namespace ASEngine;

class SpringCollisionSystem: public System<Spring, CollisionBox2D, Transform2D>
{
public:
	static inline bool Collide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
	{
		return s_Instance->ICollide(playerCollisionBox2D, playerTransform2D);
	}

private:
	static SpringCollisionSystem* s_Instance;
	bool ICollide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D);

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_SPRINGCOLLISIONSYSTEM_H