#ifndef SYSTEM_PEARLCOLLISIONSYSTEM_H
#define SYSTEM_PEARLCOLLISIONSYSTEM_H

#include "components/Objects/Pearl.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/PhysicsSystem2D/CollisionSystem2D.h"
#include "ASEngine.h"

using namespace ASEngine;

class PearlCollisionSystem: public System<Pearl, CollisionBox2D, Transform2D>
{
public:
	static inline bool Collide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
	{
		return s_Instance->ICollide(playerCollisionBox2D, playerTransform2D);
	};

private:
	static PearlCollisionSystem* s_Instance;
	bool ICollide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D);

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_PEARLCOLLISIONSYSTEM_H