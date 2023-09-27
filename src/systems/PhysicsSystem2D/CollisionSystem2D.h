#ifndef SYSTEM_COLLISIONSYSTEM2D_H
#define SYSTEM_COLLISIONSYSTEM2D_H

#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

#define COLLISION_PRECISION 0.00001f

using namespace ASEngine;

struct CollisionInfo
{
	vec2 Intersection = vec2::ZERO();
	bool Collision = false;
};

class CollisionSystem2D: public System<CollisionBox2D, Transform2D>
{
public:
	// get rectangle correct transform
	static void CalculateRectanglePosition(const CollisionBox2D &collisionBox2D, const Transform2D &src, vec2 &dest);
	
	// is a colliding with b
	static void CollisionBetween(const CollisionBox2D &a_CollisionBox2D, const Transform2D &a_Transform2D, const CollisionBox2D &b_CollisionBox2D, const Transform2D &b_Transform2D, CollisionInfo& pCollisionInfo);
	

private :
// system instance
static CollisionSystem2D *s_Instance;

	// default events
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_COLLISIONSYSTEM2D_H