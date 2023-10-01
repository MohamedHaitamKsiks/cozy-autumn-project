#include "GrassCollisionSystem.h"

GrassCollisionSystem* GrassCollisionSystem::s_Instance = nullptr;

void GrassCollisionSystem::ICollisionWithGrass(const PlayerController &playerController, const CollisionBox2D &playerCollisionBox2D, const Transform2D &playerTransform2D)
{
	ForEach([&playerController, &playerCollisionBox2D, &playerTransform2D] (GrassParticles2D& grassParticles2D, CollisionBox2D& collisionBox2D, Transform2D& transform2D)
	{
		CollisionInfo info;
		CollisionSystem2D::CollisionBetween(playerCollisionBox2D, playerTransform2D, collisionBox2D, transform2D, info);

		grassParticles2D.OnPression = info.Collision && playerController.OnGround;
		grassParticles2D.PressionPosition = playerTransform2D.Position.x - transform2D.Position.x;

	});
}

void GrassCollisionSystem::OnCreate()
{
    s_Instance = this;
};

void GrassCollisionSystem::OnUpdate(float delta)
{
	// insert code ...
};

void GrassCollisionSystem::OnRender2D()
{
	// insert code ...
};

void GrassCollisionSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
