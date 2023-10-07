#ifndef SYSTEM_LEAFCOLLISIONSYSTEM_H
#define SYSTEM_LEAFCOLLISIONSYSTEM_H

#include "ASEngine.h"

#include "components/Objects/Leaf.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/PhysicsSystem2D/CollisionSystem2D.h"
#include "systems/PlayerSystem/ScoreSystem.h"

using namespace ASEngine;

class LeafCollisionSystem: public System<Leaf, CollisionBox2D, Transform2D>
{
public:
	static inline bool Collide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
	{
		return s_Instance->ICollide(playerCollisionBox2D, playerTransform2D);
	}

private:
	static LeafCollisionSystem *s_Instance;
	bool ICollide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D);

	void OnCreate();

};

#endif // SYSTEM_LEAFCOLLISIONSYSTEM_H