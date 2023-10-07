#ifndef SYSTEM_KILLAREACOLLISIONSYSTEM_H
#define SYSTEM_KILLAREACOLLISIONSYSTEM_H

#include "components/KillArea/KillArea.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/PhysicsSystem2D/CollisionSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class KillAreaCollisionSystem: public System<KillArea, CollisionBox2D, Transform2D>
{

public:
	static inline bool Collide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
	{
		return s_Instance->ICollide(playerCollisionBox2D, playerTransform2D);
	}
	

private : 
	static KillAreaCollisionSystem *s_Instance;
	bool ICollide(const CollisionBox2D& playerCollisionBox2D, const Transform2D& playerTransform2D);

	void OnCreate();
};

#endif // SYSTEM_KILLAREACOLLISIONSYSTEM_H