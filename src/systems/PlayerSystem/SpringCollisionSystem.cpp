#include "SpringCollisionSystem.h"

SpringCollisionSystem* SpringCollisionSystem::s_Instance = nullptr;

bool SpringCollisionSystem::ICollide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
{
    bool Collision = false;
	ForEach([&Collision, &playerCollisionBox2D, &playerTransform2D](Spring& spring, CollisionBox2D &collisionBox2D, Transform2D &transform2D)
	{
		CollisionInfo collisionInfo;
		CollisionSystem2D::CollisionBetween(playerCollisionBox2D, playerTransform2D, collisionBox2D, transform2D, collisionInfo);

		if (collisionInfo.Collision)
		{
			Collision = true; 
			spring.Collision = true;
		}
		
	});

	return Collision;
}

void SpringCollisionSystem::OnCreate()
{
    s_Instance = this;
};

void SpringCollisionSystem::OnUpdate(float delta)
{
	// insert code ...
};

void SpringCollisionSystem::OnRender2D()
{
	// insert code ...
};

void SpringCollisionSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
