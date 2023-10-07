#include "KillAreaCollisionSystem.h"

KillAreaCollisionSystem* KillAreaCollisionSystem::s_Instance = nullptr;

bool KillAreaCollisionSystem::ICollide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
{
    bool Collision = false;
	ForEach([&Collision, &playerCollisionBox2D, &playerTransform2D](KillArea& killArea, CollisionBox2D& collisionBox2D, Transform2D& transform2D)
	{
		CollisionInfo collisionInfo;
		CollisionSystem2D::CollisionBetween(playerCollisionBox2D, playerTransform2D, collisionBox2D, transform2D, collisionInfo);

		if (collisionInfo.Collision)
			Collision = true;
	});

	return Collision;
}

void KillAreaCollisionSystem::OnCreate()
{
	s_Instance = this;
};
