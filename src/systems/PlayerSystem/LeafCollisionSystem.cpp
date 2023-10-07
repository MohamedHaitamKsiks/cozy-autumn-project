#include "LeafCollisionSystem.h"

LeafCollisionSystem * LeafCollisionSystem::s_Instance = nullptr;

bool LeafCollisionSystem::ICollide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
{
	bool Collision = false;
	ForEach([&Collision, &playerCollisionBox2D, &playerTransform2D](Leaf& leaf, CollisionBox2D &collisionBox2D, Transform2D &transform2D)
	{
		if (!leaf.Enable) return;

		CollisionInfo collisionInfo;
		CollisionSystem2D::CollisionBetween(playerCollisionBox2D, playerTransform2D, collisionBox2D, transform2D, collisionInfo);

		if (collisionInfo.Collision)
		{
			// disable leaf
			leaf.Enable = false;
			Collision = true; 

		}
	});

	return Collision;
}

void LeafCollisionSystem::OnCreate()
{
	s_Instance = this;
}
