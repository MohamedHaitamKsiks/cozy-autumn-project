#include "PearlCollisionSystem.h"

PearlCollisionSystem *PearlCollisionSystem::s_Instance = nullptr;

bool PearlCollisionSystem::ICollide(const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
{
	bool Collision = false;
	ForEach([&Collision, &playerCollisionBox2D, &playerTransform2D](Pearl &pearl, CollisionBox2D &collisionBox2D, Transform2D &transform2D)
	{
		if (!pearl.Enabled) return;

		CollisionInfo collisionInfo;
		CollisionSystem2D::CollisionBetween(playerCollisionBox2D, playerTransform2D, collisionBox2D, transform2D, collisionInfo);

		if (collisionInfo.Collision)
		{
			// disable leaf
			pearl.Enabled = false;
			pearl.Timer = PEARL_TIMER;
			Collision = true; 

		} 
	});

	return Collision;
}

void PearlCollisionSystem::OnCreate()
{
    s_Instance = this;
};

void PearlCollisionSystem::OnUpdate(float delta)
{
	// insert code ...
};

void PearlCollisionSystem::OnRender2D()
{
	// insert code ...
};

void PearlCollisionSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
