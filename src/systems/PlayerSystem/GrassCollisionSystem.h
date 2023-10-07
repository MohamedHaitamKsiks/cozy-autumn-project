#ifndef SYSTEM_GRASSCOLLISIONSYSTEM_H
#define SYSTEM_GRASSCOLLISIONSYSTEM_H

#include "components/Player/PlayerController.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"
#include "components/Particles2D/GrassParticles2D.h"

#include "systems/PhysicsSystem2D/CollisionSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class GrassCollisionSystem: public System<GrassParticles2D, CollisionBox2D, Transform2D>
{
public:
	static inline void CollisionWithGrass(const PlayerController &playerController, const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
	{
		s_Instance->ICollisionWithGrass(playerController, playerCollisionBox2D, playerTransform2D);
	};

private:
	static GrassCollisionSystem* s_Instance;
	void ICollisionWithGrass(const PlayerController &playerController, const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D);
	
	void OnCreate();

};

#endif // SYSTEM_GRASSCOLLISIONSYSTEM_H